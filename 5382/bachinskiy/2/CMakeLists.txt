cmake_minimum_required(VERSION 3.6)
project(OOPFigures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(lib/googletest-master/googletest)
add_subdirectory(src)

include_directories(lib/googletest-master/googletest/include)
set(SOURCE_FILES main.cpp src/Shape.h src/Shape.cpp src/Circle.h src/Circle.cpp
        src/Pentangle.h src/Pentangle.cpp src/RegularPentangle.h src/RegularPentangle.cpp)
add_executable(OOPFigures ${SOURCE_FILES})
target_link_libraries(OOPFigures gtest gtest_main)