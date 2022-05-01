
void euler(
    double &t, double &yn, double h,
    const double &derivs(const double &, const double &))
{
    yn += h * derivs(t, yn);
    t += h;
}


void rk4(double &t, double &yn, double h,
           const double &derivs(const double &, const double &))
{
    double
        k1 = derivs(t, yn),
        k2 = derivs(t + h/2, yn + h*k1/2),
        k3 = derivs(t + h/2, yn + h*k2/2),
        k4 = derivs(t + h, yn + h*k3);
    
    yn += 1/6 * h * (k1 + 2*k2 + 2*k3 + k4);
    t += h;
}


// Runge-Kutta-Cash-Karp including error estimate
void rkck(double &t, double &yn, double h,
          const double &derivs(const double &, const double &))
{
    // Butcher tableau of RKCK
    const double
        b21 = 1.0/5.0, b31 = 3.0/40.0, b41 = 3.0/10.0,
        b51 = -11.0/54.0, b61 = 1631.0/55296.0, b32 = 9.0/40.0,
        b42 = -9.0/10.0, b52 = 5.0/2.0, b62 = 175.0/512.0, b43 = 6.0/5.0,
        b53 = -70.0/27.0, b63 = 575.0/13824.0, b54 = 35.0/27.0,
        b64 = 44275.0/110592.0, b65 = 253.0/4096.0,
        c1 = 37.0/378.0, c2 = 0.0, c3 = 250.0/621.0,
        c4 = 125.0/594.0, c5 = 0.0, c6 = 512.0/1771.0,
        dc1 = c1 - 2825.0/27648.0, dc2 = c2 - 0.0,
        dc3 = c3 - 18575.0/48384.0, dc4 = c4 - 13525.0/55296.0,
        dc5 = c5 - 277.0/14336.0, dc6 = c6 - 1.0/4.0;

    double
        k1 = h * derivs(t),
        k2 = h * derivs(t + b21*k1),
        k3 = h * derivs(t + b31*k1 + b32*k2),
        k4 = h * derivs(t + b41*k1 + b42*k2 + b43*k3),
        k5 = h * derivs(t + b51*k1 + b52*k2 + b53*k3 + b54*k4),
        k6 = h * derivs(t + b61*k1 + b62*k2 + b63*k3 + b64*k4 + b65*k5);

    yn += c1*k1 + c2*k2 + c3*k3 + c4*k4 + c5*k5 + c6*k6;
    x_err = dc1*k1 + dc2*k2 + dc3*k3 + dc4*k4 + dc5*k5 + dc6*k6;
    t += h
}


// Fehlberg's 4(5) method
// Runge-Kutta-Fehlberg including error estimate
void rkf(double &t, double &yn, double &yerr, double h,
         const double &derivs(const double &, const double &))
{
  // Butcher tableau of RKF
  const double
    b21 = 1.0/4.0, b31 = 3.0/32.0, b41 = 1932.0/2197.0,
    b51 = 439.0/216.0, b61 = -8.0/27.0, b32 = 9.0/32.0,
    b42 = -7200.0/2197.0, b52 = -8.0, b62 = 2.0, b43 = 7296.0/2197.0,
    b53 = 3680.0/513.0, b63 = -3544.0/2565.0, b54 = -845.0/4104.0,
    b64 = 1859.0/4104.0, b65 = -11.0/40.0,
    c1 = 16.0/135.0, c2 = 0.0, c3 = 6656.0/12825.0,
    c4 = 28561.0/56430.0, c5 = -9.0/50.0, c6 = 2.0/55.0,
    dc1 = c1 - 25.0/216.0, dc2 = c2 - 0.0,
    dc3 = c3 - 1408.0/2565.0, dc4 = c4 - 2197.0/4104.0,
    dc5 = c5 + 1.0/5.0, dc6 = c6 - 0.0;

  vector2d
    k1 = dx * derivates(x),
    k2 = dx * derivates(x + b21*k1),
    k3 = dx * derivates(x + b31*k1 + b32*k2),
    k4 = dx * derivates(x + b41*k1 + b42*k2 + b43*k3),
    k5 = dx * derivates(x + b51*k1 + b52*k2 + b53*k3 + b54*k4),
    k6 = dx * derivates(x + b61*k1 + b62*k2 + b63*k3 + b64*k4 + b65*k5);
  
  x += c1*k1 + c2*k2 + c3*k3 + c4*k4 + c5*k5 + c6*k6;
  x_err = dc1*k1 + dc2*k2 + dc3*k3 + dc4*k4 + dc5*k5 + dc6*k6;
}