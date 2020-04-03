//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_POINT_H
#define OOP_LB1__2_POINT_H


struct Point{
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) { }


    bool operator!=(Point &other) const
    {
        return x != other.x || y != other.y;
    }

    bool operator==(Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(Point other) const
    {
        return x != other.x || y != other.y;
    }

    bool operator==(Point other) const
    {
        return x == other.x && y == other.y;
    }
};


#endif //OOP_LB1__2_POINT_H
