/*
#  -------------------------------------------------------------------------
#
#   field.hpp
#   Author: Balázs Pál, 2022
#
#   Implements a vector class to store fields used during PDE integration.
#
#
#  -------------------------------------------------------------------------
*/

#ifndef FIELD_H
#define FIELD_H

#include <vector>


class Field
{
    public:
        int N;     // Number of gridpoints
        double h;  // Finite difference of gridpoints
        std::vector<double> v;

        Field(const int n);
        Field(const int n, const double x0, const double x1);
        ~Field();
};


Field::Field(const int n)
{
    N = n;
    h = 1.0;

    for(int i=0; i < N; i++) { v.push_back(i*h); }
}

Field::Field(const int n, const double x0, const double x1)
{
    N = n;
    // h = (b - a) / (# of gridpoints - 1)
    h = (x1 - x0) / (N - 1);

    for(int i=0; i < N; i++) { v.push_back(i*h); }
}

Field::~Field()
{}

#endif