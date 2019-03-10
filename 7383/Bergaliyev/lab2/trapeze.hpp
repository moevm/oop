#pragma once
#include "shape.hpp"
#include <iostream>

class Trapeze : public Shape {
public:
    Trapeze(Color color, Point v1, Point v2, Point v3, Point v4);
    void scale(double scale_ratio);
    void relocate(Point p);
    void rotate(double angle);
    std::ostream & print(std::ostream & ostream) const;
private:
    Point v1;
    Point v2;
    Point v3;
    Point v4;
};
