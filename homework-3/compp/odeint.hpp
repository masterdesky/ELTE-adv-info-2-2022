
/*

Parameters:
yn  :  
*/
void euler(
    double &t,   // Function domain
    double &yn,  // Function codomain
    double h,   // Step size
    const double &derivs(const double &, const double &)
);

void rk4(
    double &t,
    double &yn,
    double h,
    const double &derivs(const double &, const double &)
);

void rkck(
    double &t,
    double &yn,
    double h,
    const double &derivs(const double &, const double &)
);