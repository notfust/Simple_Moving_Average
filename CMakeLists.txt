cmake_minimum_required(VERSION 3.25)
project(stc)

set(CMAKE_CXX_STANDARD 17)

add_compile_options( -O0)

add_executable(stc main.cpp)
