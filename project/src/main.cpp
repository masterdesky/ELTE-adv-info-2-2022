#include <iostream>
#include <fstream>
#include <cmath>

#include "field.hpp"
#include "pdeint.hpp"


double f_init(const double &x)
{
    return 0.2*exp(x);
}


// Use the central difference to approximate the derivatives
auto derivate(const std::vector<double> &u, const Field &x)
{
    std::vector<double> du (x.N);
    du[0] = pdeint::fw(u[1], u[0], x.v[1], x.v[0]);
    for(int i=1; i < x.N-1; i++)
    {
        du[i] = pdeint::ce(u[i+1], u[i-1], x.v[i+1], x.v[i-1]);
    }
    du[x.N-1] = pdeint::bw(u[x.N-1], u[x.N-2], x.v[x.N-1], x.v[x.N-2]);
    
    return du;
}


int main(int argc, char const *argv[])
{
    int N = 50;
    double nu = 0.1;

    std::ofstream
        file_ftcs, file_btcs, file_crnc, file_mccr;
    file_ftcs.open("../data/burgers1d_ftcs.dat");
    file_btcs.open("../data/burgers1d_btcs.dat");
    file_crnc.open("../data/burgers1d_crnc.dat");
    file_mccr.open("../data/burgers1d_mccr.dat");

    auto t = Field(N, 0, 1);
    auto x = Field(N, 0, 5);

    std::vector<double> u(N);
    for(int i=0; i < N; i++) { u[i] = f_init(x.v[i]); }

    // Burgers 1D
    // du/dt = nu * du2 / dx2 - u * du/dx
    std::vector<double> dudt (N);
    std::vector<double> dudx;
    std::vector<double> dudx2;

    // Implement the FTCS method
    auto u_curr = u;
    for(const auto &ti : t.v)
    {
        dudx = derivate(u_curr, x);
        dudx2 = derivate(dudx, x);
        for(int i=0; i < N; i++) { dudt[i] = nu * dudx2[i] - u_curr[i] * dudx[i]; }
        
        auto u_old = u_curr;
        for(int i=0; i < N; i++) { u_curr[i] = u_old[i] + dudt[i] * t.h; }
        for(const auto &ui : u_curr) { file_ftcs << ui << " "; }
        file_ftcs << std::endl;
    }

    // Implement the BTCS method
    auto u_curr = u;
    for(const auto &ti : t.v)
    {
        
        
        for(const auto &ui : u_curr) { file_ftcs << ui << " "; }
        file_btcs << std::endl;
    }

    // Implement the Crank-Nicolson method
    auto u_curr = u;
    for(const auto &ti : t.v)
    {
        dudx = derivate(u_curr, x);
        dudx2 = derivate(dudx, x);
        for(int i=0; i < N; i++) { dudt[i] = nu * dudx2[i] - u_curr[i] * dudx[i]; }
        
        auto u_old = u_curr;
        for(int i=0; i < N; i++) { u_curr[i] = u_old[i] + dudt[i] * t.h; }
        for(const auto &ui : u_curr) { file_ftcs << ui << " "; }
        file_crnc << std::endl;
    }

    file.close();

    return 0;
}
