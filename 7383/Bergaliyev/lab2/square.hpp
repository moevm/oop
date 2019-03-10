#pragma once
#include "shape.hpp"
#include <iostream>

class Square : public Shape {
public:
    Square(Color color, Point center, Point v);
    void scale(double scale_ratio);
    void relocate(Point p);
    void rotate(double angle);
    std::ostream & print(std::ostream & ostream) const;
private:
    Point v;
};
