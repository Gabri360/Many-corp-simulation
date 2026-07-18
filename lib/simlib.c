#include "../head/simlib_struct.h"
#include "../head/simlib.h"
#include "../head/simlib_base.h"


double energy_e(obj p[],int n, double G,double C)
{
    double E=0.0,d=0.0, s=5;
    for(int i=0;i<n;i++)
    {
        for(int u=i+1;u<n;u++)
        {
            d=dist(p[i],p[u]);
            E+=G*p[i].q*p[u].q/d+pow(10,C)*(pow(s/d,12))/(G);
        }
        for(int j=0;j<DIM;j++)
        {
            E+=0.5*p[i].m*(p[i].v[j]*p[i].v[j]);
        }
    }
    return E;
}

int verify_d(obj p[],int i)
{
    int v=1;
    double d=0.0,th=0.05;
    for(int j=0;j<i;j++)
    {
        d=dist(p[i],p[j]);
        if(d<th)
        {
            v=0;
            break;
        }
    }
    return v;
}

void init_P(obj p[],int e,int pr,double G,double C,double ke_init,double kp_init,int orbit)
{
    double E=0;
    int v=1;
    srand((unsigned int) time(NULL));
    while(1)
    {
        for(int i=0;i<e;i++){do
        {
            p[i].m=1;
            p[i].q=-1.0;
            for(int q=0;q<DIM;q++)
            {
                p[i].x[q]=myrand()*0.9;
                p[i].v[q]=myrand()*ke_init;
                p[i].a[q]=0.0;
            }
            p[i].colore[0]=0.3f;    
            p[i].colore[1]=0.0f;    
            p[i].colore[2]=1.0f;
            v=verify_d(p,i);
        }while(v==0);}
        for(int i=e;i<e+pr;i++){do
        {
            p[i].m=1800.0;
            p[i].q=1.0;
            for(int q=0;q<DIM;q++)
            {
                p[i].x[q]=myrand()*0.9;
                p[i].v[q]=myrand()*kp_init;
                p[i].a[q]=0.0;
            }
            p[i].colore[0]=1.0f;     
            p[i].colore[1]=0.0f;    
            p[i].colore[2]=0.0f;
            v=verify_d(p,i);
        }while(v==0);}
        E=energy_e(p,e+pr,G,C);
        if(E<0||orbit==0)
            break;
    }
}

void Init_trail(trail_o trail[],int n)
{
    for(int i=0;i<n;i++)
    {
        trail[i].head=0;
        trail[i].nb=0;
    }
}

void Init_circ(circ *E)
{
    E->head=0;
    E->nb=0;
}

void trail_agg(obj p[],int n, trail_o trail[])
{
    coord pos_att;
    for(int i=0;i<n;i++)
    {
        for(int q=0;q<DIM;q++)
        {
            pos_att.x[q]=p[i].x[q];
        }
        trail[i].history[trail[i].head]=pos_att;
        trail[i].head = (trail[i].head + 1) % (MAX_TRAIL);
        if(trail[i].nb<MAX_TRAIL)
            trail[i].nb++;
    }
}

void circ_agg(double v, circ *E)
{
            E->history[E->head]=v;
            E->head = (E->head + 1) % (MAX_ENERGY);
            if(E->nb<MAX_ENERGY)
                E->nb++;
}

void force(obj p[],int n,int i,double G,double C)
{
    double s=5;
    for(int q=0;q<DIM;q++)
    {
        p[i].a[q]=0;
    }
    for(int j=0;j<n;j++)
    {
        if(i!=j)
        {
            double d=dist(p[i],p[j]);
            
                for(int q=0;q<DIM;q++)
                {
                    p[i].a[q]-=G*p[j].q*p[i].q*(p[j].x[q]-p[i].x[q])/(p[i].m*d*d*d);
                    p[i].a[q]-=pow(10,C)*(p[j].x[q]-p[i].x[q])*(12*pow(s/d,14)/(s*s))/(G*p[i].m);
                }
        }
    }
}


coord acc(double x[DIM], double qe,double m,int j, obj p[],int n,double G,double C)
{
    coord a;
    for(int f=0;f<DIM;f++)
    {
        a.x[f]=0;
    }
    double s=5;
    for(int i=0;i<n;i++)
    {
        if(i!=j)
        {
            double d=dist_q(x,p[i].x);
            for(int q=0;q<DIM;q++)
            {
                a.x[q]+=G*qe*p[i].q*(x[q]-p[i].x[q])/(m*d*d*d);
                a.x[q]+=pow(10,C)*(x[q]-p[i].x[q])*(12*pow(s/d,14)/(s*s))/(G*m);
            }
            
        }
    }
    return a;
}


