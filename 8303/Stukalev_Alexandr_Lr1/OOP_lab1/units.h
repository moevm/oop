#ifndef UNITS_H
#define UNITS_H

#include "statics.h"

class Unit:public Health, public Armor, public Damage
{
public:
    int x;
    int y;
    char designation;
    void move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

struct Point
{
    int x;
    int y;
    Point(int X, int Y) : x(X), y(Y) {}
    Point() :x(0), y(0) {}

    bool operator!=(Point &other) {
        return x != other.x || y != other.y;
    }
    bool operator!=(Point other) {
        return x != other.x || y != other.y;
    }
    bool operator==(Point other) {
        return x == other.x && y == other.y;
    }

};
#endif // UNITS_H
