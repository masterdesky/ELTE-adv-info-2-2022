#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323


double f(double x0)
{
    double y0 = sin(x0);

    return y0;
}


// Inputs are `x_{i}` and `x_{i+1}`
double f_FW(double x0, double x1)
{
    double y0 = (f(x1) - f(x0)) / (x1 - x0);

    return y0;
}


// Inputs are `x_{i-1}` and `x_{i}`
double f_BW(double x_1, double x0)
{
    double y0 = (f(x0) - f(x_1)) / (x0 - x_1);

    return y0;
}


int main(int argc, char const *argv[])
{
    size_t N = 64;
    double dx = 4 * PI / (N - 1);

    // Define `x`
    double x[N];
    for(size_t i = 0; i < N; i++)
    {
        x[i] = i*dx;
    }
    fprintf(stdout, "f(x):\n");
    for(size_t i = 0; i < N; i++) { fprintf(stdout, "%g ", x[i]); }
    fprintf(stdout, "\n\n");


    // Calculate the `y` values
    double y[N];

    for(size_t i = 0; i < N; i++)
    {
        y[i] = f(x[i]);
    }
    fprintf(stdout, "f(x):\n");
    for(size_t i = 0; i < N; i++) { fprintf(stdout, "%g ", y[i]); }
    fprintf(stdout, "\n\n");


    // Calculate the `y_FW` derivative using forward differentiation
    double y_FW[N];

    for(size_t i = 0; i < N-1; i++)
    {
        y_FW[i] = f_FW(x[i], x[i+1]);
    }
    y_FW[N] = f_BW(x[N-2], x[N-1]);
    fprintf(stdout, "f(x) after calculating f_FW(x):\n");
    for(size_t i = 0; i < N; i++) { fprintf(stdout, "%g ", y[i]); }
    fprintf(stdout, "\n\n");
    

    // Print the results to a file
    FILE *fp = fopen("diff.dat", "w+");
    for(size_t i = 0; i < N; i++)
    {
        fprintf(fp, "%g,%g,%g\n", x[i], y[i], y_FW[i]);
    }
    fclose(fp);


    return 0;
}
