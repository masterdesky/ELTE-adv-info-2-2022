#include <iostream>
#include <fstream>
#include <cmath>

#include "field.hpp"
#include "pdeint.hpp"


// Define Pi with great precision and calculate it during compilation time
constexpr double pi() { return std::atan(1)*4; }


// Set initial conditions for the 1D Burgers' equation
double f_init(const double &x, const double &nu)
{   
    double t = 0;
    double phi = 
        exp(- pow((-4*t + x - 2*pi()), 2) / (4 * nu * (t + 1)))
      + exp(- pow((-4*t + x), 2) / (4 * nu * (t + 1)));
    double phi_prime =
      - (-8*t + 2*x) / (4 * nu * (t + 1))
      * exp(- pow((-4*t + x), 2) / (4 * nu * (t + 1)))
      - (-8*t + 2*x - 4*pi()) / (4 * nu * (t+1))
      * exp(- pow((-4 * t + x - 2*pi()), 2) / (4 * nu * (t + 1)));
    
    return -2 * nu * phi_prime/phi + 4;
}


// Use the central difference to approximate the derivatives
auto derivate(const std::vector<double> &u, const Field &x)
{
    // Using periodic boundary conditions
    std::vector<double> du (x.N);
    for(int i=0; i < x.N; i++)
    {
        int i1  = ((x.N-1)+i+1)%(x.N-1);
        int i_1 = ((x.N-1)+i-1)%x.N;
        du[i] = pdeint::ce(u[i1], u[i_1], x.v[i1], x.v[i_1]);

    }
    return du;
}


int main(int argc, char const *argv[])
{
    int Nx = 200;
    int Nt = 50;
    double nu = 0.8;

    std::ofstream file;
    file.open("../data/burgers1d.dat");

    auto t = Field(Nt);
    auto x = Field(Nx, 0, 2*pi());

    std::vector<double> u(Nx);
    for(int i=0; i < Nx; i++) { u[i] = f_init(x.v[i], nu); }
    // Write initial conditions to file
    for(const auto &ui : u) { file << ui << " "; }
    file << std::endl;

    // Burgers 1D
    // du/dt = nu * du2 / dx2 - u * du/dx
    std::vector<double> dudt (Nx);
    std::vector<double> dudx;
    std::vector<double> dudx2;

    // Implement the FTCS method
    auto u_curr = u;
    for(int ti=1; ti < Nt; ti++)
    {
        t = t.v[ti];
        dudx = derivate(u_curr, x);
        dudx2 = derivate(dudx, x);
        for(int i=0; i < Nx; i++) { dudt[i] = nu * dudx2[i] - u_curr[i] * dudx[i]; }
        
        auto u_old = u_curr;
        for(int i=0; i < Nx; i++) { u_curr[i] = u_old[i] + dudt[i] * t.h; }

        // Write to file
        for(const auto &ui : u_curr) { file << ui << " "; }
        file << std::endl;
    }

    file.close();

    return 0;
}
