#ifndef SIMLIB_BASE
#define SIMLIB_BASE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double dist(obj a, obj b);

double dist_q(double x1[DIM], double x2[DIM]);

double media(double v[],int n);

double deviazione_standard(double v[],int n);

double myrand();

void read_config(int *e,int *pr,double  *A,double *C,double *ut);

#endif