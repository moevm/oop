#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>

struct Point2d
{
    double x;
    double y;

    Point2d(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    double distance(Point2d p) const;
};

#endif // POINT2D_H
