#include "../head/simlib_struct.h"
#include "../head/simlib_metodi.h"
#include "../head/simlib.h"
void eulero(obj p[],int n,double dt,double G,double C)
{
    for(int i=0;i<n;i++)
    {
        coord a;
        a=acc(p[i].x,p[i].q,p[i].m,i,p,n,G,C);
        for(int q=0;q<DIM;q++)
        {
            p[i].a[q]=a.x[q];
            p[i].v[q]+=p[i].a[q]*dt;
            p[i].x[q]+=p[i].v[q]*dt;
        }

        for(int q=0;q<DIM;q++)
        {
            if (p[i].x[q] > 1.0f||p[i].x[q] < -1.0f) { p[i].v[q] =-p[i].v[q];}
        }
    }
}

void RK4(obj p[],int n,double dt,double G, double C)
{
    for(int i=0;i<n;i++)
    {
        coord k_q[4];
        coord k_v[4];
        coord a;
        double temp[DIM];
        for(int q=0;q<DIM;q++)
        {
            k_q[0].x[q]=p[i].v[q];
            k_v[0].x[q]=acc(p[i].x,p[i].q,p[i].m,i,p,n,G,C).x[q];
        }

        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+dt*k_q[0].x[q]/2;
        }
        for(int q=0;q<DIM;q++)
        {
            k_q[1].x[q]=p[i].v[q]+dt*k_v[0].x[q]/2;
            k_v[1].x[q]=acc(temp,p[i].q,p[i].m,i,p,n,G,C).x[q];
        }
    
        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+dt*k_q[1].x[q]/2;
        }
        for(int q=0;q<DIM;q++)
        {
            k_q[2].x[q]=p[i].v[q]+dt*k_v[1].x[q]/2;
            k_v[2].x[q]=acc(temp,p[i].q,p[i].m,i,p,n,G,C).x[q];
        }
    
        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+dt*k_q[2].x[q];
        }
        for(int q=0;q<DIM;q++)
        {
            k_q[3].x[q]=p[i].v[q]+dt*k_v[2].x[q];
            k_v[3].x[q]=acc(temp,p[i].q,p[i].m,i,p,n,G,C).x[q];
        }

        for(int q=0;q<DIM;q++)
        {
            p[i].x[q]+=dt*(k_q[0].x[q]+2*k_q[1].x[q]+2*k_q[2].x[q]+k_q[3].x[q])/6;
            p[i].v[q]+=dt*(k_v[0].x[q]+2*k_v[1].x[q]+2*k_v[2].x[q]+k_v[3].x[q])/6;

        }

        for(int q=0;q<DIM;q++)
        {
            if (p[i].x[q] > 1.0f||p[i].x[q] < -1.0f) { p[i].v[q] =-p[i].v[q];}
        }
    }
}

void RK45(obj p[],int n,double *dt,double tol,double G, double C)
{
    coord a;
    state *y4=malloc(n*sizeof(state));
    state *y5=malloc(n*sizeof(state));
    while(1){
    double error=0.0;
    for(int i=0;i<n;i++)
    {
        coord k_q[6];
        coord k_v[6];
        double temp[DIM];

        a=acc(p[i].x,p[i].q,p[i].m,i,p,n,G,C);
        for(int q=0;q<DIM;q++)
        {
            k_q[0].x[q]=p[i].v[q]**dt;
            k_v[0].x[q]=a.x[q]**dt;
        }

        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+0.25*k_q[0].x[q];
        }
        a=acc(temp,p[i].q,p[i].m,i,p,n,G,C);

        for(int q=0;q<DIM;q++)
        {
            k_q[1].x[q]=*dt*(p[i].v[q]+0.25*k_v[0].x[q]);
            k_v[1].x[q]=a.x[q]**dt;
        }

        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+(3.0/32.0)*k_q[0].x[q]+(9.0/32.0)*k_q[1].x[q];
        }
        a=acc(temp,p[i].q,p[i].m,i,p,n,G,C);
        for(int q=0;q<DIM;q++)
        {
            k_q[2].x[q]=*dt*(p[i].v[q]+(3.0/32.0)*k_v[0].x[q]+(9.0/32.0)*k_v[1].x[q]);
            k_v[2].x[q]=a.x[q]**dt;
        }

        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+(1932.0/2197.0)*k_q[0].x[q]-(7200.0/2197.0)*k_q[1].x[q]+(7296.0/2197.0)*k_q[2].x[q];
        }
        a=acc(temp,p[i].q,p[i].m,i,p,n,G,C);
        for(int q=0;q<DIM;q++)
        {
            k_q[3].x[q]=*dt*(p[i].v[q]+(1932.0/2197.0)*k_v[0].x[q]-(7200.0/2197.0)*k_v[1].x[q]+(7296.0/2197.0)*k_v[2].x[q]);
            k_v[3].x[q]=a.x[q]**dt;
        }

        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]+(439.0/216.0)*k_q[0].x[q]-8*k_q[1].x[q]+(3680.0/513.0)*k_q[2].x[q]-(845.0/4104.0)*k_q[3].x[q];
        }
        a=acc(temp,p[i].q,p[i].m,i,p,n,G,C);
        for(int q=0;q<DIM;q++)
        {
            k_q[4].x[q]=*dt*(p[i].v[q]+(439.0/216.0)*k_v[0].x[q]-8*k_v[1].x[q]+(3680.0/513.0)*k_v[2].x[q]-(845.0/4104.0)*k_v[3].x[q]);
            k_v[4].x[q]=a.x[q]**dt;
        }

        for(int q=0;q<DIM;q++)
        {
            temp[q]=p[i].x[q]-(8.0/27.0)*k_q[0].x[q]+2*k_q[1].x[q]-(3544.0/2565.0)*k_q[2].x[q]+(1859.0/4104.0)*k_q[3].x[q]-(11.0/40.0)*k_q[4].x[q];
        }
        a=acc(temp,p[i].q,p[i].m,i,p,n,G,C);
        for(int q=0;q<DIM;q++)
        {
            k_q[5].x[q]=*dt*(p[i].v[q]-(8.0/27.0)*k_v[0].x[q]+2*k_v[1].x[q]-(3544.0/2565.0)*k_v[2].x[q]+(1859.0/4104.0)*k_v[3].x[q]-(11.0/40.0)*k_v[4].x[q]);
            k_v[5].x[q]=a.x[q]**dt;
        }

        for(int q=0;q<DIM;q++)
        {
            y4[i].x[q]=p[i].x[q]+(25.0/216.0)*k_q[0].x[q]+(1408.0/2565.0)*k_q[2].x[q]+(2197.0/4104.0)*k_q[3].x[q]-(1.0/5.0)*k_q[4].x[q];
            y4[i].v[q]=p[i].v[q]+(25.0/216.0)*k_v[0].x[q]+(1408.0/2565.0)*k_v[2].x[q]+(2197.0/4104.0)*k_v[3].x[q]-(1.0/5.0)*k_v[4].x[q];

            y5[i].x[q]=p[i].x[q]+(16.0/135.0)*k_q[0].x[q]+(6656.0/12825.0)*k_q[2].x[q]+(28561.0/56430.0)*k_q[3].x[q]-(9.0/50.0)*k_q[4].x[q]+(2.0/55.0)*k_q[5].x[q];
            y5[i].v[q]=p[i].v[q]+(16.0/135.0)*k_v[0].x[q]+(6656.0/12825.0)*k_v[2].x[q]+(28561.0/56430.0)*k_v[3].x[q]-(9.0/50.0)*k_v[4].x[q]+(2.0/55.0)*k_v[5].x[q];
        }

        for(int q=0;q<DIM;q++)
        {
            error+=(y5[i].x[q]-y4[i].x[q])*(y5[i].x[q]-y4[i].x[q])+(y5[i].v[q]-y4[i].v[q])*(y5[i].v[q]-y4[i].v[q]);
        }    
    }
    error=sqrt(error);
    if(error<tol)
    {
        for(int i=0;i<n;i++)
        {
            for(int q=0;q<DIM;q++)
            {
                p[i].x[q]=y5[i].x[q];
                p[i].v[q]=y5[i].v[q];
            }

            for(int q=0;q<DIM;q++)
            {
                if (p[i].x[q] > 1.0f||p[i].x[q] < -1.0f) { p[i].v[q] =-p[i].v[q];}
            }
        }
        break;
    }
    else
        *dt*=pow(tol/error,1.0/5.0);
    }
    free(y4);
    free(y5);
}

void verlet_v(obj p[],int n,double dt,double G,double C)
{
    coord new_acc;
    for(int i=0;i<n;i++)
    {
        for(int q=0;q<DIM;q++)
        {
            p[i].x[q]+=p[i].v[q]*dt+0.5*p[i].a[q]*dt*dt;
        }

        new_acc=acc(p[i].x,p[i].q,p[i].m,i,p,n,G,C);

        for(int q=0;q<DIM;q++)
        {
            p[i].v[q]+=0.5*(p[i].a[q]+new_acc.x[q])*dt;
            p[i].a[q]=new_acc.x[q];
        }

        for(int q=0;q<DIM;q++)
        {
            if (p[i].x[q] > 1.0f||p[i].x[q] < -1.0f) { p[i].v[q] =-p[i].v[q];}
        }
    }
}