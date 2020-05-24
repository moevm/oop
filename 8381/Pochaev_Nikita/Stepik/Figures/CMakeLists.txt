cmake_minimum_required(VERSION 3.15)
project(Stepic)

set(CMAKE_CXX_STANDARD 14)

add_executable(Stepic main.cpp Figures/BasePoint.cpp Figures/BasePoint.h Subsidiary/Information.h Figures/Shape.cpp Figures/Shape.h Subsidiary/ANSIColor.cpp Subsidiary/ANSIColor.h Subsidiary/IGeometricObject.h Figures/Circle.cpp Figures/Circle.h Figures/Rhombus.cpp Figures/Rhombus.h Figures/IShape.h Figures/Trapezoid.cpp Figures/Trapezoid.h)