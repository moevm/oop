#include "point.h"

Point::Point(int x, int y): x(x), y(y){}


void Point::operator=(const Point &point){
    x = point.x;
    y = point.y;
}


void Point::operator+=(const Point &point){
    x += point.x;
    y += point.y;
}


void Point::operator-=(const Point &point){
    x -= point.x;
    y -= point.y;
}


bool Point::operator==(const Point &point){
    if (x == point.x && y == point.y)
        return 1;
    else return 0;
}


Point Point::operator+(const Point &point){
    return Point{
        x + point.x,
        y + point.y
    };
}


Point Point::operator-(const Point &point){
    return Point{
        x - point.x,
        y - point.y
    };
}
