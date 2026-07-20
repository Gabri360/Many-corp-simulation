#ifndef SIMLIB_STRUCT
#define SIMLIB_STRUCT
#define MAX_TRAIL 3000
#define MAX_ENERGY 3000
#define DIM 4

typedef struct {
    double x[DIM];
} coord;

typedef struct {
    double x[DIM];
    double v[DIM];
} state;


typedef struct {
    coord history[MAX_TRAIL];
    int head,nb;
} trail_o;

typedef struct {
    double history[MAX_ENERGY];
    int head,nb;
}circ;

typedef struct 
{
    double x[DIM];
    double a[DIM];
    double v[DIM];
    double m,q;
    float colore[3];
}obj;

#endif