#ifndef SIMLIB_METODI
#define SIMLIB_METODI


void eulero(obj p[],int n,double dt,double G,double C);

void RK4(obj p[],int n,double dt,double G,double C);

void RK45(obj p[],int n,double *dt,double tol,double G, double C);

void verlet_v(obj p[],int n,double dt,double G,double C);
#endif