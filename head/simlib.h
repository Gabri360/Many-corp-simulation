#ifndef SIMUL_LIB
#define SIMUL_LIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include <GLFW/glfw3.h>
#define MAX_FRAME 10000

double energy_e(obj p[],int n, double G,double C);

int verify_d2(obj p[],int i);

void init_P(obj p[],int e,int pr,double G,double C,double ke_init,double kp_init,int orbit);

void Init_trail(trail_o trail[],int n);

void Init_circ(circ *E);

void trail_agg(obj p[],int n, trail_o trail[]);

void circ_agg(double v, circ *E);

void force(obj p[],int n,int i,double G,double C);

coord acc(double x[DIM], double q,double m,int j, obj p[],int n,double G,double C);

void saveFrame(GLFWwindow* window);
#endif