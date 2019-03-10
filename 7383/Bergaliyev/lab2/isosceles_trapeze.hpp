#pragma once
#include "shape.hpp"
#include <iostream>

class Isosceles_Trapeze : public Shape {
public:
    Isosceles_Trapeze(Color color, Point center, Point v1, Point v2); //v1, v2 - вершины при боковой стороне
    void scale(double scale_ratio);
    void relocate(Point p);
    void rotate(double angle);
    std::ostream & print(std::ostream & ostream) const;
private:
    Point v1;
    Point v2;
};
