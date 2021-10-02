cmake_minimum_required(VERSION 3.17)
project(CovidDataset_v2)

set(CMAKE_CXX_STANDARD 14)

add_executable(CovidDataset_v2 main.cpp AVL.h AVL.cpp Node.hpp Node.cpp Country.hpp Country.cpp)