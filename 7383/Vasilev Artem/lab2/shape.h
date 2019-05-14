#ifndef SHAPE_H
#define SHAPE_H

#include "color.h"
#include "point.h"
#include <iostream>
#include <cstdlib>

class Shape
{
public:
    Shape();
    Shape(Color &color);
    Color getColor();
    void setColor(const Color& newColor);
    int getID() const;
    virtual void move(const Point& center) = 0;
    virtual void rotate(double angle = 0) = 0;
    virtual void scale(double coefficient = 1) = 0;
    Color color;
    static int global_id;
private:
    int id;
    int count = 0;
};



#endif // SHAPE_H
