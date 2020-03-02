#ifndef POINT_H
#define POINT_H


struct Point2i
{
    int x;
    int y;

    Point2i();
    Point2i(int x, int y);
    Point2i(const Point2i& other);

    Point2i operator+(const Point2i& rPoint);
    Point2i operator-(const Point2i& rPoint);

    Point2i& operator+=(const Point2i& rPoint);
    Point2i& operator-=(const Point2i& rPoint);

    Point2i& operator=(const Point2i& rPoint);

    bool operator==(const Point2i& rPoint);
};

#endif // POINT_H
