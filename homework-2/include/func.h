#include <math.h>


double f(double* x0)
{
    double y0 = sin(*x0);

    return y0;
}


double f_FW(double* x0, double* x1)
{
    double y0 = (*x1 - *x0) / (f(x1) - f(x0));

    return y0;
}


double f_BW(double* x0, double* x_1)
{
    double y0 = (*x0 - *x_1) / (f(x0) - f(x_1));

    return y0;
}


double f_CE(double* x1, double* x_1)
{
    double y0 = (*x1 - *x_1) / (f(x1) - f(x_1));

    return y0;
}


double f_AN(double* x0)
{
    double y0 = cos(*x0);

    return y0;
}