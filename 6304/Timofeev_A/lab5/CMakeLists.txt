cmake_minimum_required (VERSION 3.10)

project(lab5)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_library(algs algs.cpp)
add_library(shape figures.cpp)
add_library(basis basis.cpp)

add_executable (lab5 lab5.cpp)
add_executable (tests tests.cpp)

target_link_libraries(lab5 algs shape basis)
target_link_libraries(tests algs shape basis)

target_compile_features(lab5 PUBLIC cxx_std_11)
target_compile_features(tests PUBLIC cxx_std_11)