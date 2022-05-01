#include<cmath>

#include "vector.hpp"

//  take a single Euler step
void EulerStep(
    Vector &x,
    double tau,
    Vector derivs(const Vector &x)
);

//  take a single Euler step
void EulerCromerStep(
    Vector &x,
    double tau,
    Vector derivs(const Vector &x)
);