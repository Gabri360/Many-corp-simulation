#include "../head/simlib_struct.h"
#include "../head/simlib_base.h"

double dist(obj a, obj b)
{
    double sum=0;
    for(int i=0;i<DIM;i++)
    {
        sum+=(a.x[i]-b.x[i])*(a.x[i]-b.x[i]);
    }
    return sqrt(sum);
}

double dist_q(double x1[DIM], double x2[DIM])
{
    double sum=0;
    for(int i=0;i<DIM;i++)
    {
        sum+=(x1[i]-x2[i])*(x1[i]-x2[i]);
    }
    return sqrt(sum);
}

double media(double v[],int n) 
{
    double somma = 0.0;
    for(int i=0;i<n;i++) 
    {
        somma += v[i];
    }
    return somma / (double)n;
}

double deviazione_standard(double v[],int n) 
{
    double m = media(v,n);
    double somma = 0.0;

    for(int i=0;i<n;i++) 
    {
        somma += (v[i]-m)*(v[i]-m);
    }

    return sqrt(somma / (double)n);
}

inline double myrand()
{
    return ((double)rand() / RAND_MAX) * 2.0 - 1.0;
}
