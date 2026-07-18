#include "../head/simlib_struct.h"
#include "../head/simlib.h"
#include "../head/simlib_base.h"
#include "../head/simlib_metodi.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../head/stb_image_write.h"

int main() {

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "sim", NULL, NULL);
    GLFWwindow* graf = glfwCreateWindow(1920, 1080, "graf", NULL, NULL);
    int width, height;
    
    int e=200;
    int pr=200;

    int n=e+pr;
    double A=10;            //Quanti armstrong è lunga metà simulazione
    double C=-11.1;         //Efficacia del potenziale di collisione
    double ut=5e-7;         //Unità di tempo della simulazione
    double dt=4e-7, G=2.3e-6/(A*ut*ut), E0, t=0, ke_init=1e2, kp_init=1e2, tol=10e-5;
    circ E, err;
    trail_o *trail=malloc(n*sizeof(trail_o));
    obj *p = malloc(n * sizeof(obj));
    init_P(p,e,pr,G,C,ke_init,kp_init,0);
    Init_trail(trail,n);
    Init_circ(&E);
    Init_circ(&err);
    E0=energy_e(p,n,G,C);
    
//----------------------------------------------------------------------------------------------------------------        

    while (!glfwWindowShouldClose(window)&&!glfwWindowShouldClose(graf)) 
    {
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if(DIM<4)
            glPointSize(15.0f);

        
        for(int i=0;i<n;i++)
        {
            if(DIM>=4)
                glPointSize(15.0*(p[i].x[3]+1.4)/2.4);
            glBegin(GL_POINTS);
            if(DIM==2)
                glColor4d(p[i].colore[0],p[i].colore[1],p[i].colore[2],1.0);
            if(DIM>=3)
                glColor4d(p[i].colore[0],p[i].colore[1],p[i].colore[2],(p[i].x[2]+1.4)/2.4);
            glVertex2d(p[i].x[0], p[i].x[1]); 
            glEnd();

            glBegin(GL_LINE_STRIP);
            if(DIM==2)
                glColor4d(p[i].colore[0], p[i].colore[1], p[i].colore[2],0.3f);
            for (int j=0;j<trail[i].nb;j++) 
            {
                int idx = (trail[i].head+j-trail[i].nb+MAX_TRAIL) % MAX_TRAIL;
                if(DIM>=3)
                    glColor4d(p[i].colore[0], p[i].colore[1], p[i].colore[2],0.7*(trail[i].history[idx].x[2]+1.1)/2.1);
                glVertex2d(trail[i].history[idx].x[0],trail[i].history[idx].x[1]);
            }
            glEnd();        
        }
        glfwSwapBuffers(window);

        glfwMakeContextCurrent(graf);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glfwGetFramebufferSize(graf, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(2);
        glBegin(GL_LINES);
            glColor4f(1.0f, 1.0f, 1.0f,0.3f);
            glVertex2d(-1.0,0.0); glVertex2d(1.0,0.0);
            glVertex2d(-0.8,-1.0); glVertex2d(-0.8,1.0);
        glEnd();

        glPointSize(4);
        glBegin(GL_POINTS);
        glColor4f(1.0f, 0.9f, 0.9f,1.0f);
        for(int i=0;i<E.nb;i++)
        {
            glColor4f(1.0f, 0.9f, 0.9f,1.0f); 
            int idx = (E.head+i-E.nb+MAX_ENERGY) % MAX_ENERGY;
            glVertex2d((t-i*3e-7)*2e4-0.8,(E.history[idx]/E0)-1);
            glColor4f(1.0f, 0.0f, 0.0f,0.6f);
            glVertex2d((t-i*3e-7)*2e4-0.8,(err.history[idx]));
        }
        glEnd();
        glfwSwapBuffers(graf);
         
//----------------------------------------------------------------------------------------------------------------        


        //verlet_v(p,n,dt,G,C);
        //RK4(p,n,dt,G,C);
        //eulero(p,n,dt,G,C);
        RK45(p,n,&dt,tol,G,C);

        if(t<MAX_ENERGY*3e-7)
            t+=3e-7;
        trail_agg(p,n,trail);
        
        circ_agg(energy_e(p,n,G,C),&E);
        
        double md=media(E.history,E.nb),std=deviazione_standard(E.history,E.nb);
        printf("(%lf%%)----\t%e +- %e\t%e\n",fabs(std*100.0/md),md,std,dt);

        circ_agg(fabs(std*100.0/md), &err);

//----------------------------------------------------------------------------------------------------------------        
    
    //saveFrame(window);


    glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    free(p);
    free(trail);
    return 0;
}