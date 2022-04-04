#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "str.h"
#include "func.h"
#include "secure_io.h"


#define PI 3.14159265358979323


int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        fprintf(stdout, "Usage: ./diff <N>\n");
        exit(EXIT_FAILURE);
    }
    size_t N = (size_t) strtoul(argv[1], NULL, 10);
    double dx = 4 * PI / (N-1);

    // Define `x`
    double x[N];
    for(size_t i = 0; i < N; i++)
    {
        x[i] = i*dx;
    }
    fprintf(stdout, "x:\n"); print(x, N);


    // Calculate the `y` values
    double y[N];

    for(size_t i = 0; i < N; i++)
    {
        y[i] = f(x[i]);
    }
    fprintf(stdout, "y:\n"); print(y, N);


    // Calculate the `y_FW` derivative using forward differentiation
    double y_FW[N];

    for(size_t i = 0; i < N-1; i++)
    {
        y_FW[i] = f_FW(x[i], x[i+1]);
    }
    y_FW[N-1] = f_BW(x[N-2], x[N-1]);
    fprintf(stdout, "y_FW :\n"); print(y, N);


    // Calculate the `y_BW` derivative using backward differentiation
    double y_BW[N];

    y_BW[0] = f_FW(x[0], x[1]);
    for(size_t i = 1; i < N; i++)
    {
        y_BW[i] = f_BW(x[i-1], x[i]);
    }


    // Calculate the `y_CE` derivative using central differentiation
    double y_CE[N];

    y_CE[0] = f_FW(x[0], x[1]);
    for(size_t i = 1; i < N-1; i++)
    {
        y_CE[i] = f_CE(x[i-1], x[i+1]);
    }
    y_CE[N-1] = f_BW(x[N-2], x[N-1]);


    // Calculate the `y_AN` derivative using the analytic formula
    double y_AN[N];

    for(size_t i = 0; i < N; i++)
    {
        y_AN[i] = f_AN(x[i]);
    }
    

    // Print the results to a file
    //FILE *fp = open_file();
    FILE *fp = fopen("./data/diff.dat", "w+");
    for(size_t i = 0; i < N; i++)
    {
        fprintf(fp, "%g\t%g\t%g\t%g\t%g\t%g\n",
                    x[i], y[i], y_FW[i], y_BW[i], y_CE[i], y_AN[i]);
    }
    fclose(fp);


    return 0;
}
