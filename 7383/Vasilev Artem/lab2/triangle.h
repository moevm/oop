#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
public:
    Triangle();
    Triangle(Point& center, Point& p1, Point& p2, Point& p3);
    Triangle(Color& color);
    void scale(double coefficient);
    void rotate(double angle);
    void move(const Point& center);


    friend std::ostream& operator << (std::ostream &print, Triangle& triangle);

private:
    double coefficient = 1;
    double a; //длины сторон
    double b;
    double c;
    Point p1, p2, p3; //координаты вершин
    Point center;
};

#endif // TRIANGLE_H
