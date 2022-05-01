#include <iostream>

#include "vector.hpp"


int main(int argc, char const *argv[])
{
    auto v = vector3d(5, 2, 1);
    auto v2 = v;

    std::cout << v2 << std::endl;
}