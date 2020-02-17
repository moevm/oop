#ifndef POINT_H
#define POINT_H


struct Point{
    int x;
    int y;

    Point(int x, int y);

    void operator= (const Point &point);
    void operator+=(const Point &point);
    void operator-=(const Point &point);
    bool operator==(const Point &point);

    Point operator+(const Point &point);
    Point operator-(const Point &point);
};

#endif // POINT_H
