/*

Parameters:
yn  :  
*/
void euler(
    double &t,      // Function domain
    double &yn,     // Function codomain
    double &ynerr,  // Error of integration
    double h,       // Step size
    const double &derivs(const double &, const double &)
);

void rk4(
    double &t,      // Function domain
    double &yn,     // Function codomain
    double &ynerr,  // Error of integration
    double h,       // Step size
    const double &derivs(const double &, const double &)
);

void rkck(
    double &t,      // Function domain
    double &yn,     // Function codomain
    double &ynerr,  // Error of integration
    double h,       // Step size
    const double &derivs(const double &, const double &)
);

void rkf(
    double &t,      // Function domain
    double &yn,     // Function codomain
    double &ynerr,  // Error of integration
    double h,       // Step size
    const double &derivs(const double &, const double &)
);