cmake_minimum_required(VERSION 3.23)

project(odeint)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(odeint src/main.cpp)

# Add the compp library
add_subdirectory(compp)
target_link_libraries(odeint PUBLIC compp)
target_include_directories(odeint PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/compp"
                          )
