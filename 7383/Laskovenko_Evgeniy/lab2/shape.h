#include <iostream>
#include <string>
#include <vector>
#include "header.h"

#ifndef SHAPE_H
#define SHAPE_H


class Shape
{
protected:
    unsigned id;
    Color clr;
    Point centre;
    std::vector<Point> crd;

private:
    //Pure-virtual (non-used) functions:
    virtual void set_crd() = 0;

public:
    Shape(Point cntr);
    Color get_color() const;
    void set_color(Color);

    //Pure-virtual functions:
    virtual void move(Point) = 0;
    virtual void rotate(double) = 0;
    virtual void scale(double) = 0;

    //Virtual functions:
    virtual ~Shape();

    //Friend functions:
    friend std::ostream& operator<<(std::ostream&, const Shape&);
};

#endif // SHAPE_H
