cmake_minimum_required(VERSION 3.18)

project(pdeint)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executables for different equations
add_executable(pdeint1d src/burgers1d.cpp)
target_include_directories(pdeint1d PUBLIC include/)

add_executable(pdeint2d src/burgers2d.cpp)
target_include_directories(pdeint2d PUBLIC include/)