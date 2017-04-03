#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle
{
public:
    Square(const Point2d vertex, double side, double angle = 0) : Rectangle(vertex, side, side, angle) {}

};

#endif // SQUARE_H
