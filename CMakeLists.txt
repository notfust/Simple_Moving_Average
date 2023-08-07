cmake_minimum_required(VERSION 3.25)
project(stc)

set(CMAKE_CXX_STANDARD 17)

set(MY_COMPILE_FLAGS "-O")
add_definitions(${MYCOMPILE_FLAGS})

add_executable(stc main.cpp)
