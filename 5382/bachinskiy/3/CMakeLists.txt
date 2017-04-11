cmake_minimum_required(VERSION 3.6)
project(3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)

set(SOURCE_FILES main.cpp list.cpp)
add_executable(3 ${SOURCE_FILES})