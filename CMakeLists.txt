cmake_minimum_required(VERSION 3.23)
project(TP3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
add_executable(TP3 ex01_copier-vecteur-avx.cpp)
