#ifndef PARALLELOGRAMM_H
#define PARALLELOGRAMM_H

#include "shape.h"

class Parallelogramm : public Shape
{
public:
    Parallelogramm();
    Parallelogramm(Point& center, Point& p1, Point& p2, Point& p3, Point& p4);
    Parallelogramm(Color& color);
    void scale(double coefficient);
    void rotate(double angle);
    void move(const Point& center);
    friend std::ostream& operator << (std::ostream &print, Parallelogramm& parallelogramm);

private:
    Point p1, p2, p3, p4;
    Point center;
    double coefficient = 1;
    double a;
    double b;
    double c;
    double d;
};


#endif // PARALLELOGRAMM_H
