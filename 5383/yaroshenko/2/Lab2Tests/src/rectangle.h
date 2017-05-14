#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"
#include "triangle.h"

class Rectangle : public Polygon
{
public:
    // center - координаты верхней левой вершины
    Rectangle(const Point2d& vertex, double _upperSide, double _leftSide, double angle = 0);
    Rectangle(double random_range = 100);

    double area() const;
    double perimeter() const;

    void scale(double scale = 1);

    double getUpperSide() const;
    double getLeftSide() const;

    static void split(Rectangle* rect, Triangle* part1, Triangle* part2);

protected:
    // Стороны прямоугольника
    double upperSide, leftSide;

    void print(std::ostream &os) const override;
};

#endif // RECTANGLE_H
