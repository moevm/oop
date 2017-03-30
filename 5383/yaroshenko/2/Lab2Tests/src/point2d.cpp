#include "point2d.h"

double Point2d::distance(Point2d p) const
{
    double dx = p.x - x;
    double dy = p.y - y;

    return sqrt(dx*dx + dy*dy);
}
