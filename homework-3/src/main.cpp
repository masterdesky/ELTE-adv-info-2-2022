#include <iostream>
#include <array>

#include "odeint.hpp"

#define N 500

double f(double const &t)
{
    return t*t / 2.0;
}

double derivs(double const &t, double const yn)
{
    return f(t);
}


std::array<double, N> ode_solve(std::array<double, N> const &t, double const y0)
{
    std::array<double, N>
        vsolve, verr;
    // Initial values
    // y(0) = 1
    double yn = y0;
    double ynerr = 0;
}

int main(int argc, char const *argv[])
{
    double t_min = 0, t_max = 1;
    double dt = (t_max - t_min) / (N - 1);

    // Array to contain time steps
    std::array<double, N> t;
    for(int i = 0; i < N; i++) { t[i] = i * dt; }

    // Arrays to contain values of derivs
    std::array<double, N>
        veuler, vrk4, vrkck, vrkf;
}