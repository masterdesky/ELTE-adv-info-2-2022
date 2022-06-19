/*
#  -------------------------------------------------------------------------
#
#   pdeint.hpp
#   Author: Balázs Pál, 2022
#
#   Implements the finite-difference method to numerically solve the Burgers'
#   equation using multiple integration methods.
#
#
#  -------------------------------------------------------------------------
*/

#ifndef PDEINT_H
#define PDEINT_H

#include "field.hpp"

namespace pdeint
{
    // Finite difference approximation of derivatives if `f()` is known
    // x_i   : The `i`th value
    // x_i1  : The `i+1`th value
    // x_i_1 : The `i-1`th value
    double fw(double f(const double &),
              const double x_i1, const double x_i)
    {
        return (f(x_i1) - f(x_i)) / (x_i1 - x_i);
    }
    double bw(double f(const double &),
              const double x_i, const double x_i_1)
    {
        return (f(x_i) - f(x_i_1)) / (x_i - x_i_1);
    }
    double ce(double f(const double &),
              const double x_i1, const double x_i_1)
    {
        return (f(x_i1) - f(x_i_1)) / (x_i1 - x_i_1);
    }

    // Finite difference approximation of derivatives if only the y(xi)
    // values are known
    double fw(const double T_i1, const double T_i,
              const double x_i1, const double x_i)
    {
        return (T_i1 - T_i) / (x_i1 - x_i);
    }
    double bw(const double T_i, const double T_i_1,
              const double x_i, const double x_i_1)
    {
        return (T_i - T_i_1) / (x_i - x_i_1);
    }
    double ce(const double T_i1, const double T_i_1,
              const double x_i1, const double x_i_1)
    {
        return (T_i1 - T_i_1) / (x_i1 - x_i_1);
    }
};

#endif
