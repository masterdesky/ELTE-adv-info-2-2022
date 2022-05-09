#include "odeint.hpp"

void euler(double &t, double &yn, double &ynerr,
           double h,
           double const &derivs(double const &, double const &))
{
    yn += h * derivs(t, yn);
    ynerr = 1.0/2.0 * h * h * derivs(t, yn);
    t += h;
}


void rk4(double &t, double &yn, double &ynerr,
         double h,
         double const &derivs(double const &, double const &))
{
    // Butcher tableau of RK4
    double const
        c2 = 1.0/2.0, c3 = 1.0/2.0, c4 = 1.0;
    double const
        a21 = 1.0/2.0,
        a32 = 1.0/2.0,
        a43 = 1.0;
    double const
        b1 = 1.0/6.0, b2 = 1.0/3.0, b3 = 1.0/3.0, b4 = 1.0/6.0;

    double
        k1 = derivs(t, yn),
        k2 = derivs(t + c2*h, yn + h*(a21*k1)),
        k3 = derivs(t + c3*h, yn + h*(a32*k2)),
        k4 = derivs(t + c4*h, yn + h*(a43*k3));
    
    yn += h * (b1*k1 + b2*k2 + b3*k3 + b4*k4);
    ynerr = 0;
    t += h;
}


// Runge-Kutta-Cash-Karp 4(5) including error estimate
void rkck(double &t, double &yn, double &ynerr,
          double h,
          double const &derivs(double const &, double const &))
{
    // Butcher tableau of RKCK
    double const
        c2 = 1.0/5.0, c3 = 3.0/10.0, c4 = 3.0/5.0, c5 = 1.0, c6 = 7.0/8.0;
    double const
        a21 = 1.0/5.0,
        a31 = 3.0/40.0, a32 = 9.0/40.0,
        a41 = 3.0/10.0, a42 = -9.0/10.0, a43 = 6.0/5.0,
        a51 = -11.0/54.0, a52 = 5.0/2.0, a53 = -70.0/27.0, a54 = 35.0/27.0,
        a61 = 1661.0/55296.0, a62 = 175.0/512.0, a63 = 575.0/13824.0, a64 = 44275.0/110592.0, a65 = 253.0/4096.0;
    double const
        b1 = 2825.0/27648.0, b2 = 0.0, b3 = 18575.0/48384.0,
        b4 = 13525.0/55296.0, b5 = 277.0/14336.0, b6 = 1.0/4.0;
    double const
        db1 = b1 - 37.0/378.0, db2 = b2 - 0.0, db3 = b3 - 250.0/621.0,
        db4 = b4 - 125.0/594.0, db5 = b5 - 0.0, db6 = b6 - 512.0/1771.0;

    double
        k1 = h * derivs(t, yn),
        k2 = h * derivs(t + c2*h, yn + h*(a21*k1)),
        k3 = h * derivs(t + c3*h, yn + h*(a31*k1 + a32*k2)),
        k4 = h * derivs(t + c4*h, yn + h*(a41*k1 + a42*k2 + a43*k3)),
        k5 = h * derivs(t + c5*h, yn + h*(a51*k1 + a52*k2 + a53*k3 + a54*k4)),
        k6 = h * derivs(t + c6*h, yn + h*(a61*k1 + a62*k2 + a63*k3 + a64*k4 + a65*k5));

    yn += h * (b1*k1 + b2*k2 + b3*k3 + b4*k4 + b5*k5 + b6*k6);
    ynerr = db1*k1 + db2*k2 + db3*k3 + db4*k4 + db5*k5 + db6*k6;
    t += h;
}


// Fehlberg's 4(5) method
// Runge-Kutta-Fehlberg including error estimate
void rkf(double &t, double &yn, double &ynerr,
         double h,
         double const &derivs(double const &, double const &))
{
    // Butcher tableau of RKF
    double const
        c2 = 1.0/4.0, c3 = 3.0/8.0, c4 = 12.0/13.0, c5 = 1.0, c6 = 1.0/2.0;
    double const
        a21 = 1.0/4.0,
        a31 = 3.0/32.0, a32 = 9.0/32.0,
        a41 = 1932.0/2197.0, a42 = -7200.0/2197.0, a43 = 7296.0/2197.0,
        a51 = 439.0/216.0, a52 = -8.0, a53 = 3680.0/513.0, a54 = -845.0/4104.0,
        a61 = -8.0/27.0, a62 = 2.0, a63 = -3544.0/2565.0, a64 = 1859.0/4104.0, a65 = -11.0/40.0;
    double const
        b1 = 16.0/135.0, b2 = 0.0, b3 = 6656.0/12825.0,
        b4 = 28561.0/56430.0, b5 = -9.0/50.0, b6 = 2.0/55.0;
    double const
        db1 = b1 - 25.0/216.0, db2 = b2 - 0.0, db3 = b3 - 1408.0/2565.0,
        db4 = b4 - 2197.0/4104.0, db5 = b5 + 1.0/5.0, db6 = b6 - 0.0;

    double
        k1 = h * derivs(t, yn),
        k2 = h * derivs(t + c2*h, yn + h*(a21*k1)),
        k3 = h * derivs(t + c3*h, yn + h*(a31*k1 + a32*k2)),
        k4 = h * derivs(t + c4*h, yn + h*(a41*k1 + a42*k2 + a43*k3)),
        k5 = h * derivs(t + c5*h, yn + h*(a51*k1 + a52*k2 + a53*k3 + a54*k4)),
        k6 = h * derivs(t + c6*h, yn + h*(a61*k1 + a62*k2 + a63*k3 + a64*k4 + a65*k5));

    yn += h * (b1*k1 + b2*k2 + b3*k3 + b4*k4 + b5*k5 + b6*k6);
    ynerr = db1*k1 + db2*k2 + db3*k3 + db4*k4 + db5*k5 + db6*k6;
    t += h;
}