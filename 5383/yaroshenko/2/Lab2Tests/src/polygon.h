#ifndef POLYGON_H
#define POLYGON_H

#include <stdexcept>
#include <cmath>
#include <vector>

#include "shape.h"
#include "point2d.h"


class Polygon : public Shape
{
public:
    Polygon(std::vector<Point2d> v) : Shape(), vertices(v) {}

    void translate2d(Point2d dp);
    void rotate(double angle = 0);
    void scale(double scale = 1);

protected:
    // Вершины многоугольника
    std::vector<Point2d> vertices;

    void print(std::ostream& os) const;
};

#endif // POLYGON_H
