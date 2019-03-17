#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H
#include "triangle.h"


class RightTriangle : public Triangle
{
public:
    RightTriangle();
    RightTriangle(const Point A, double a, double b, const RGB _colour);
    friend std::ostream& operator<<(std::ostream& os, RightTriangle& s);
};

#endif // RIGHTTRIANGLE_H
