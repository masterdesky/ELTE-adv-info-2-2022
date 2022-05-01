#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "vector.hpp"
#include "odeint.hpp"


//  Simple Euler
void EulerStep(Vector &x, double tau,
               Vector derivates(const Vector&))
{   
    // Time
    // Deflection
    // Velocity
    x += tau * derivates(x);
}

//  Semi-Implicit, Euler-Cromer
void EulerCromerStep(Vector &x, double tau,
                     Vector derivates(const Vector&))
{
    auto x_temp = x;

    x_temp.x += tau * derivates(x).x;  // Time
    x_temp.z += tau * derivates(x).z;  // Velocity
    x_temp.y += tau * x_temp.z;        // Deflection

    x = x_temp;
}