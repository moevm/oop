#include "point.h"
#include <math.h>

Point::Point() : x(0), y(0)
{

}

Point::Point(double x, double y)
    : x(x)
    , y(y)
{

}

double Point::length(Point& point) {
    return sqrt((x-point.x)*(x-point.x) + (y-point.y)*(y-point.y));
}

void Point::rotate(double angle) {
    double newX = x;
    double newY = y;
    x = newX * cos(angle*pi/180) - newY * sin(angle*pi/180);
    y = newX * sin(angle*pi/180) + newY * cos(angle*pi/180);
}
