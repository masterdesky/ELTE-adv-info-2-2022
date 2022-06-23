#include <iostream>
#include <fstream>
#include <cmath>

#include "field.hpp"
#include "pdeint.hpp"


// Define Pi with great precision and calculate it during compilation time
constexpr double pi() { return std::atan(1)*4; }


// Set initial conditions for the 1D Burgers' equation
double f_init1(const double &x, const double &nu)
{
    double t = 0.0;
    double phi =
        exp(- pow((-4*t + x - 2*pi()), 2) / (4 * nu * (t+1)))
      + exp(- pow((-4*t + x), 2) / (4 * nu * (t+1)));
    double phi_prime = \
      - (-8*t + 2*x) / (4 * nu * (t+1))
      * exp(- pow((-4*t + x), 2) / (4 * nu * (t+1)))
      - (-8*t + 2*x - 4*pi()) / (4 * nu * (t+1))
      * exp(- pow((-4*t + x - 2*pi()), 2) / (4 * nu * (t+1)));

    return -2*nu*(phi_prime/phi) + 4;
}

double f_init2(const double &x, const Field &X)
{
    return (-2 * sin(X.h * x)) / (cos(X.h * x) * exp(-0.1));
}


auto ftcs(const std::vector<double> &u,
          const Field &x, const Field &t, const double &nu)
{
    double dt = t.h, dx = x.h;
    
    auto u_n = u;
    // Boundary conditions remains enforced by iterating from 1 -> N-1
    for(int i=1; i < x.N-1; i++)
    {
        u_n[i] =
            u[i]
            +
            nu * (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx) * dt
            -
            u[i] * (u[i+1] - u[i-1]) / (2*dx) * dt;
    }

    return u_n;
}


int main(int argc, char const *argv[])
{
    double
        x0 = -9.0, x1 = 9.0, dx = 0.2;
    double
        t0 = 0.0, t1 = 1.0, dt = 0.0001;
    int Nx = (x1-x0)/dx;
    int Nt = (t1-t0)/dt;
    double nu = 0.07;

    std::ofstream file;
    file.open("../data/burgers1d.dat");

    //auto x = Field(Nx, 0, 2*pi());
    auto x = Field(Nx, x0, x1);
    auto t = Field(Nt, t0, t1);

    // Set initial conditions
    std::vector<double> u(x.N);
    //for(int i=0; i < x.N; i++) { u[i] = f_init1(x.v[i], nu); }
    for(int i=0; i < x.N; i++) { u[i] = f_init2(x.v[i], x); }
    // Write initial conditions to file
    for(const auto &ui : u) { file << ui << " "; }
    file << std::endl;


    // Implement the FTCS method for the 1D Burgers' equation
    auto u_n = u;
    for(int ti=1; ti < t.N; ti++)
    {
        u_n = ftcs(u_n, x, t, nu);

        // Write to file
        if(ti % 1 == 0)
        {
            for(const auto &ui : u_n) { file << ui << " "; }
            file << std::endl;
        }
    }

    file.close();

    return 0;
}
