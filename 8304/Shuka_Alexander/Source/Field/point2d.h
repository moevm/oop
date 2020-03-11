#ifndef POINT2D_H
#define POINT2D_H

#include <cstddef>


class Point2D
{
public:
    explicit Point2D(size_t x, size_t y);
    ~Point2D() = default;

    Point2D(const Point2D& point);
    Point2D(Point2D&& point);

    Point2D& operator=(const Point2D& point);
    Point2D& operator=(Point2D&& point);

    size_t x;
    size_t y;
};

#endif // POINT2D_H
