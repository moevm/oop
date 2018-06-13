cmake_minimum_required(VERSION 2.8)
project(OOP_L5)
set(CMAKE_CXX_FLAGS "-std=c++11 -ggdb")

include_directories(include)

set(TEST src/source.cpp)
set(MAIN src/main.cpp)

add_executable(L5TEST ${TEST})
add_executable(L5 ${MAIN})