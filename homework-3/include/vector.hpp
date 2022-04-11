////////////////////////////////////////////////////////
//
//    Creating a custom vector class with operator
//    overloading
//
//    File : vector.hpp
//    Desc : Contains the declaration of the custom
//           vector class
//
//    Written by Balázs Pál @ 2021
//
////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <utility>

class Vector
{
  /*
  Implements an R^3 vector class, with appropriate operator overloading for
  arithmetic and string operation and more.
  Elements of the vector are always stored as double precision variables. The
  reason for this is that properly handling type conversion in case of scalar
  multiplication or division for any usecases, requires much more work than I'm
  willing to invest in.
  */

  public:
    // Storing elements of the R^3 vector
    double x, y, z;

    //----------------------------------------//
    //  0. Constructor for the vector class   //
    //----------------------------------------//
    Vector() {}
    Vector(double x_i, double y_i, double z_i)
    {
      x = x_i;
      y = y_i;
      z = z_i;
    }

    //----------------------------------------//
    //  1. Overloading arithmetic operators   //
    //----------------------------------------//

    //  1.a. Overloading arithmetic `+` and `+=` (addition)
    friend Vector operator+(Vector const& v_1, Vector const& v_2);
    Vector& operator+=(Vector const& v);

    //  1.b. Overloading arithmetic `-` and `-=` (subtraction)
    friend Vector operator-(Vector const& v_1, Vector const& v_2);
    Vector& operator-=(Vector const& v);

    //  1.c. Overloading arithmetic `*` and `*=` (scalar multiplication)
    //       from both sides
    friend Vector operator*(Vector const& v, double const& c);
    friend Vector operator*(double const& c, Vector const& v);
    Vector& operator*=(double const& c);

    //  1.d. Overloading arithmetic `/` and `/=` (scalar division)
    friend Vector operator/(Vector const& v, double const& c);
    friend Vector operator/(double const& c, Vector const& v);
    Vector& operator/=(double const& c);


    //----------------------------------------//
    //  2. Overloading string operators       //
    //----------------------------------------//

    //  2.a. Print elements of the vector with `<<`
    friend std::ostream& operator<<(std::ostream& o, Vector const& v);

    //  2.b. Add elements to vector from input stream with `>>`
    friend std::istream& operator>>(std::istream& i, Vector& v);


    //----------------------------------------//
    //  3. Adding useful methods for class    //
    //----------------------------------------//

    // 3.a. Scalar multiplication of vectors
    //
    // Always return `double`, no matter the type of the vector elements
    double dot(Vector const& v);

    // 3.b. Square of the length of the vector in Euclidean metric
    double sqlength();

    // 3.c. Length of the vector in Euclidean metric
    double length();

    // 3.d. Return the unit vector that is collinear vector
    Vector normalize();
};