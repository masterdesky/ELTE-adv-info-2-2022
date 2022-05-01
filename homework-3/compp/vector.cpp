#include <iostream>

#include "vector.hpp"

// Constructor
vector3d::vector3d(double xi, double yi, double zi)
{
    x = xi; y = yi; z = zi;
}
// Copy constructor
vector3d::vector3d(vector3d const &v)
{
    x = v.x; y = v.y; z = v.z;
}

/////////////////////////////
//
//   1. Arithmetic operators
//
/////////////////////////////////
// Arithmetic `+` and `+=`
vector3d operator+(vector3d const &v1, vector3d const &v2)
{
    return vector3d( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
}
vector3d& vector3d::operator+=(vector3d const &v)
{
    x += v.x; y += v.y; z += v.z;
    return *this;
}

// Arithmetic `-` and `-=`
vector3d operator-(vector3d const &v1, vector3d const &v2)
{
    return vector3d( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}
vector3d& vector3d::operator-=(vector3d const &v)
{
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

// Arithmetic `*` and `*=` (Dot product and scalar multiplication)
double operator*(vector3d const &v1, vector3d const &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
double vector3d::operator*=(vector3d const &v)
{
    return x * v.x + y * v.y + z * v.z;
}
vector3d operator*(vector3d const &v, double const &c)
{
    return vector3d( v.x * c, v.y * c, v.z * c );
}
vector3d operator*(double const &c, vector3d const &v)
{
    return v * c;
}
vector3d& vector3d::operator*=(double const &c)
{
    x *= c; y *= c; z *= c;
    return *this;
}

//  Arithmetic `/` (scalar division)
vector3d operator/(vector3d const &v, double const &c)
{
    if(c == 0) {
        std::cout << "[ERR] Zero division error! Vector restored." << std::endl;
        return v;
    }
    else {
        return vector3d( v.x / c, v.y / c, v.z / c );
    }
}
vector3d operator/(double const &c, vector3d const &v)
{
    std::cout << "[ERR] Division of scalar by vector is not allowed!" << std::endl;
    return vector3d ( 0, 0, 0 );
}
vector3d& vector3d::operator/=(double const &c)
{
    if(c == 0) {
        std::cout << "[ERR] Zero division error! Vector restored." << std::endl;
    }
    else {
        x /= c; y /= c; z /= c;
    }
    return *this;
}


/////////////////////////////
//
//   2. IO operators
//
/////////////////////////////////
//  Print elements of the vector with `<<`
std::ostream& operator<<(std::ostream &o, vector3d const &v)
{
  o << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
  return o;
}

//  Add elements to vector from input stream with `>>`
std::istream& operator>>(std::istream &i, vector3d &v)
{
  i >> v.x >> v.y >> v.z;
  return i;
}