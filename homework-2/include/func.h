#include <math.h>


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


// Inputs are `x_{i-1}` and `x_{i+1}`
double f_CE(double x_1, double x1)
{
    double y0 = (f(x1) - f(x_1)) / (x1 - x_1);

    return y0;
}


double f_AN(double x0)
{
    double y0 = cos(x0);

    return y0;
}
