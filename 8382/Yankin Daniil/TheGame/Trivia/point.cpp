#include "Point.h"


Point::Point(uint16_t x, uint16_t y) : x(x), y(y) {};

Point::~Point() {};


uint16_t Point::getX() const {
    return x;
}
uint16_t Point::getY() const {
    return y;
}


bool operator==(const Point& one, const Point& two) {
    if (one.x == two.x && one.y == two.y)
        return true;
    return false;
}

bool operator!=(const Point& one, const Point& two) {
    return !(one == two);
}

bool operator<(const Point& one, const Point& two) {
    if (one.y < two.y)
        return true;
    if (one.x < two.x)
        return true;
    return false;
}
