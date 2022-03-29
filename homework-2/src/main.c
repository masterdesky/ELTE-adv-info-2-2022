#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "func.h"

#define PI 3.14159265358232979

int main(int argc, char const *argv[])
{
    int N = 500;
    double dx = 4 * PI / N;
    // Define x
    double x[N];
    for(int i = 0; i < N; i++) { x[i] = i*dx; }
    for(int i = 0; i < N; i++) { fprintf(stdout, "%g ", x[i]); }
    fprintf(stdout, "\n\n");
    
    // Get function values
    double y[N];
    for(int i = 0; i < N; i++) { y[i] = f(&x[i]); }
    for(int i = 0; i < N; i++) { fprintf(stdout, "%g ", y[i]); }
    fprintf(stdout, "\n\n");

    double y_FW[N];
    for(int i = 0; i < N-1; i++) { y_FW[i] = f_FW(&x[i], &x[i+1]); }
    y_FW[N] = f_BW(&x[N], &x[N-1]);
    for(int i = 0; i < N; i++) { fprintf(stdout, "%g ", y_FW[i]); }
    fprintf(stdout, "\n\n");

    double y_BW[N];
    y_BW[0] = f_FW(&x[0], &x[1]);
    for(int i = 1; i < N; i++) { y_BW[i] = f_BW(&x[i], &x[i-1]); }
    for(int i = 0; i < N; i++) { fprintf(stdout, "%g ", y_BW[i]); }
    fprintf(stdout, "\n\n");

    double y_CE[N];
    y_BW[0] = f_FW(&x[0], &x[1]);
    for(int i = 1; i < N-1; i++) { y_CE[i] = f_BW(&x[i-1], &x[i+1]); }
    y_FW[N] = f_BW(&x[N], &x[N-1]);
    for(int i = 0; i < N; i++) { fprintf(stdout, "%g ", y_CE[i]); }
    fprintf(stdout, "\n\n");

    double y_AN[N];
    for(int i = 0; i < N; i++) { y_AN[i] = f_AN(&x[i]); }
    for(int i = 0; i < N; i++) { fprintf(stdout, "%g ", y_AN[i]); }
    fprintf(stdout, "\n\n");

    
    return 0;
}
