#include <iostream>
#include <fstream>
#include <cmath>

#include "field.hpp"
#include "pdeint.hpp"


// Define Pi with great precision and calculate it during compilation time
constexpr double pi() { return std::atan(1)*4; }


// Set initial conditions for the 1D Burgers' equation
double f_init(const double &x, const double &y)
{
    double
        mu_x = 0.0, mu_y = 0.0,
        s_x = 1.0, s_y = 1.0;

    return exp(
     - (pow((x - mu_x), 2)/(2 * pow(s_x, 2))
        +
        pow((y - mu_y), 2)/(2 * pow(s_y, 2)))
    );
}

auto ftcs(const std::vector<double> &u,
          const Field &x, const Field &y, const Field &t, const double &nu)
{
    double
        dt = t.h, dx = x.h, dy = y.h;
    
    auto u_n = u;
    // Boundary conditions remains enforced by iterating from 1 -> N-1
    for(int i=1; i < x.N-1; i++)
    {
        for(int j=0; j < y.N-1; j++)
        {
            u_n[i * y.N + j] =
                u[i * y.N + j]
                +
                nu * (
                    (u[(i+1) * y.N + j] - 2*u[i * y.N + j] + u[(i-1) * y.N + j]) / (dx*dx)
                    +
                    (u[i * y.N + (j+1)] - 2*u[i * y.N + j] + u[i * y.N + (j-1)]) / (dy*dy)
                ) * dt
                -
                u[i * y.N + j] * (
                    (u[(i+1) * y.N + j] - u[(i-1) * y.N + j]) / (2*dx)
                    +
                    (u[i * y.N + (j+1)] - u[i * y.N + (j-1)]) / (2*dy)
                ) * dt;
        }
    }

    return u_n;
}


int main(int argc, char const *argv[])
{
    double
        t0 = 0.0, t1 = 1.0, dt = 0.0001;
    double
        x0 = -5.0, x1 = 5.0, dx = 0.2,
        y0 = -5.0, y1 = 5.0, dy = 0.2;
    int
        Nt = (t1-t0)/dt,
        Nx = (x1-x0)/dx,
        Ny = (y1-y0)/dy;
    double nu = 0.07;

    std::ofstream file;
    file.open("../data/burgers2d.dat");

    //auto x = Field(Nx, 0, 2*pi());
    auto x = Field(Nx, x0, x1);
    auto y = Field(Ny, y0, y1);
    auto t = Field(Nt, t0, t1);

    // Set initial conditions
    std::vector<double> u(x.N*y.N);
    for(int i=0; i < x.N; i++)
    {
        for(int j = 0; j < y.N; j++)
        {
            u[i * y.N + j] = f_init(x.v[i], y.v[j]);
        }
    }
    // Write initial conditions to file
    for(const auto &ui : u) { file << ui << " "; }
    file << std::endl;


    // Implement the FTCS method for the 1D Burgers' equation
    auto u_n = u;
    for(int ti=1; ti < t.N; ti++)
    {
        u_n = ftcs(u_n, x, y, t, nu);

        // Write to file
        if(ti % 100 == 0)
        {
            for(const auto &ui : u_n) { file << ui << " "; }
            file << std::endl;
        }
    }

    file.close();

    return 0;
}
