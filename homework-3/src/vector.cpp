////////////////////////////////////////////////////////
//
//    Creating a custom vector class with operator
//    overloading
//
//    File : vector.cpp
//    Desc : Contains definitions to overloading operations
//           for the custom vector class
//
//    Written by Balázs Pál @ 2021
//
////////////////////////////////////////////////////////

#include <cmath>
#include <stdio.h>
#include <iostream>

#include <vector.hpp>

//----------------------------------------//
//  1. Overloading arithmetic operators   //
//----------------------------------------//

//  1.a. Overloading arithmetic `+` (addition)
Vector operator+(Vector const &v_1, Vector const &v_2)
{
  return Vector( v_1.x + v_2.x,
                   v_1.y + v_2.y,
                   v_1.z + v_2.z );
}

Vector& Vector::operator+=(Vector const& v)
{
  x += v.x;
  y += v.y;
  z += v.z;

  // Literally return THIS vector after we've changed the x and y values
  // Note the `&` after the declaration of the return type of this function
  return *this;
}


//  1.b. Overloading arithmetic `-` (subtraction)
Vector operator-(Vector const& v_1, Vector const& v_2)
{
  return Vector( v_1.x - v_2.x,
                   v_1.y - v_2.y,
                   v_1.z - v_2.z );
}
Vector& Vector::operator-=(Vector const& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;

  // Literally return THIS vector after we've changed the x and y values
  // Note the `&` after the declaration of the return type of this function
  return *this;
}


//  1.c. Overloading arithmetic `*` (scalar multiplication)
//       from both sides
Vector operator*(Vector const &v, double const &c)
{
  return Vector( v.x * c,
                   v.y * c,
                   v.z * c );
}
Vector operator*(double const &c, Vector const &v)
{
  return v * c;
}
Vector& Vector::operator*=(double const &c)
{
  x *= c;
  y *= c;
  z *= c;

  // Literally return THIS vector after we've changed the x and y values
  // Note the `&` after the declaration of the return type of this function
  return *this;
}


//  1.d. Overloading arithmetic `/` (scalar division)
Vector operator/(Vector const &v, double const &c)
{
  return Vector( v.x / c,
                   v.y / c,
                   v.z / c );
}
Vector operator/(double const &c, Vector const &v)
{
  std::cout << "Division of scalar by vector is not allowed!" << std::endl;
  return Vector ( 0, 0, 0 );
}
Vector& Vector::operator/=(double const &c)
{
  x /= c;
  y /= c;
  z /= c;

  // Literally return THIS vector after we've changed the x and y values
  // Note the `&` after the declaration of the return type of this function
  return *this;
}


//----------------------------------------//
//  2. Overloading string operators       //
//----------------------------------------//

//  2.a. Print elements of the vector with `<<`
std::ostream& operator<<(std::ostream &o, Vector const &v)
{
  o << "{ " << v.x << ", " << v.y << ", " << v.z << " }";

  return o;
}

//  2.b. Add elements to vector from input stream with `>>`
std::istream& operator>>(std::istream &i, Vector &v)
{
  i >> v.x >> v.y >> v.z;

  return i;
}


//----------------------------------------//
//  3. Adding useful methods for class    //
//----------------------------------------//

// 3.a. Scalar multiplication of vectors
//
// Always return `double`, no matter the type of the vector elements
double Vector::dot(Vector const &v)
{
  return x*v.x + y*v.y + z*v.z;
}

// 3.b. Square of the length of the vector in Euclidean metric
double Vector::sqlength()
{
  return x*x + y*y + z*z;
}

// 3.c. Length of the vector in Euclidean metric
double Vector::length()
{
  // Obviously just call the square root of the `sqlength` function
  return sqrt(this->sqlength());
}

// 3.d. Return the unit vector that is collinear to the input vector `v`
Vector Vector::normalize()
{
  // The division operator is overloaded, so we can do this
  return Vector( x / length(),
                   y / length(),
                   z / length()  );
}