cmake_minimum_required(VERSION 3.10)
project(gogolev_strategy)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES
        *.hpp
        *.cpp
        )

file(GLOB_RECURSE REMOVE_CMAKE "cmake-build-debug/*")
list(REMOVE_ITEM SOURCES ${REMOVE_CMAKE})

add_executable(gogolev_strategy ${SOURCES})