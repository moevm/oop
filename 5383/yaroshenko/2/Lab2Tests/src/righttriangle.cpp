#include "righttriangle.h"

RightTriangle::RightTriangle(const Point2d &vertex, double leftSide, double downSide, double angle) :

    Triangle(vertex,
             Point2d(vertex.x + leftSide, vertex.y),
             Point2d(vertex.x, vertex.y + downSide) )
{
    rotate(angle);
}


double RightTriangle::area() const
{
    return (0.5 * a * b);
}
