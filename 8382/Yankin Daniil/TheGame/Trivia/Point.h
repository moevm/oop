#pragma once

#include <cstdint>


class Point {
private:
    uint16_t x;
    uint16_t y;

public:
    Point(uint16_t x, uint16_t y);
    ~Point();

    uint16_t getX();
    uint16_t getY();

    friend bool operator==(const Point& one, const Point& two);
    friend bool operator!=(const Point& one, const Point& two);
    friend bool operator<(const Point& one, const Point& two);
};
