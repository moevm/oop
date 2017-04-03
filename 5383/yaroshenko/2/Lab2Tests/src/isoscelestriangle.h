#ifndef ISOSCELESTRIANGLE_H
#define ISOSCELESTRIANGLE_H

#include "triangle.h"

class IsoscelesTriangle : public Triangle
{
public:
    IsoscelesTriangle(const Point2d vertex, double side, double phi, double angle = 0);

    void scale(double scale = 1);

private:
    double h;
};

#endif // ISOSCELESTRIANGLE_H
