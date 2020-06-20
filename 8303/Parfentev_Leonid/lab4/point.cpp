#include <math.h>

#include "point.hpp"

double
Vec2::length() const
{
    return sqrt(_x*_x + _y*_y);
}

double
Vec2::distance(const Vec2 &pt) const
{
    return delta(pt).length();
}

bool
Vec2::unit() const
{
    return (_x || _y)
        && abs(_x) <= 1
        && abs(_y) <= 1;
}

bool
Vec2::adjacent(const Vec2 &pt) const
{
    return delta(pt).unit();
}
