#include "../head/simlib_struct.h"
#include "../head/simlib.h"
#include "../head/simlib_base.h"
#include "../head/simlib_metodi.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION

int main() {
    
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "sim", NULL, NULL);
    GLFWwindow* graf = glfwCreateWindow(1920, 1080, "graf", NULL, NULL);
    int width, height;
    
    
    
    double  A,  //Quanti armstrong è lunga metà simulazione
    C,          //Efficacia del potenziale di collisione
    ut;         //Unità di tempo della simulazione
    
    read_config(&A,&C,&ut);
    int e=100;
    int pr=100;
    int sim_type=4;
    
    int n=e+pr;
    double dt=9e-8, G=2.3e-6/(A*ut*ut), E0, t=0, ke_init=1e2, kp_init=1e2, tol=10e-5;
    circ E, err;
    trail_o *trail=malloc((long unsigned int) n*sizeof(trail_o));
    obj *p = malloc((long unsigned int) n*sizeof(obj));
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
            glPointSize((float) (15.0*(p[i].x[3]+1.4)/2.4));
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
        
        if(sim_type==1)
        eulero(p,n,dt,G,C);
        verlet_v(p,n,dt,G,C);
        if(sim_type==2)
        verlet_v(p,n,dt,G,C);
        if(sim_type==3)
        RK4(p,n,dt,G,C);
        if(sim_type==4)
        RK45(p,n,&dt,tol,G,C);
        
        if(t<MAX_ENERGY*3e-7)
        t+=3e-7;
        trail_agg(p,n,trail);
        
        circ_agg(energy_e(p,n,G,C),&E);
        
        double md=media(E.history,E.nb),std=deviazione_standard(E.history,E.nb);
        printf("(%lf%%)----\t%e +- %e\t%e\n",fabs(std*100.0/md),md,std,dt);
        
        circ_agg(fabs(std*100.0/md), &err);
        
        
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    free(p);
    free(trail);
    return 0;
}