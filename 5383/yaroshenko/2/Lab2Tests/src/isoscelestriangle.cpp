#include "isoscelestriangle.h"

IsoscelesTriangle::IsoscelesTriangle(const Point2d vertex, double side, double phi, double angle) :

    Triangle(vertex,
             Point2d(vertex.x - (2 * side * sin(phi / 2) / 2), vertex.y - (side * cos(phi / 2)) ),
             Point2d(vertex.x + 2 * side * sin(phi / 2) / 2, vertex.y - (side * cos(phi / 2)) ) )
{
    rotate(angle);
}


void IsoscelesTriangle::scale(double scale)
{
    h *= scale;

    Triangle::scale(scale);
}
