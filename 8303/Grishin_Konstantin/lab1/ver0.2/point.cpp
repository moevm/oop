#include "point.h"

Point2i::Point2i():
    x(-1), y(-1)
{}


Point2i::Point2i(int x, int y):
    x(x), y(y)
{}


Point2i::Point2i(const Point2i& other):
    x(other.x), y(other.y)
{}


Point2i Point2i::operator+(const Point2i &rPoint)
{
    return Point2i{x + rPoint.x, y + rPoint.y};
}


Point2i Point2i::operator-(const Point2i &rPoint)
{
    return Point2i{x - rPoint.x, y - rPoint.y};
}


Point2i& Point2i::operator+=(const Point2i &rPoint)
{
    *this = *this + rPoint;
    return *this;
}


Point2i& Point2i::operator-=(const Point2i &rPoint)
{
    *this = *this - rPoint;
    return *this;
}


Point2i& Point2i::operator=(const Point2i &rPoint)
{
    if (this != &rPoint){
        x = rPoint.x;
        y = rPoint.y;
    }
    return *this;
}


bool Point2i::operator==(const Point2i& rPoint)
{
    if(x == rPoint.x && y == rPoint.y)
        return true;
    return false;
}
