#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include <iostream>
#include <math.h>
struct Point{
    double x;
    double y;
    Point():x(0),y(0){}
    Point(double _x, double _y):x(_x), y(_y){}
};

struct RGB{
    unsigned red;
    unsigned green;
    unsigned blue;
    RGB(): red(0), green(0),blue(0){}
    RGB(unsigned r, unsigned g, unsigned b) : red(r), green(g), blue(b){}
};

class Shape
{
protected:
    int id;
    double angle;
    RGB colour;
    Point point;
    std::vector <Point> points;


public:
    Shape();
    Shape(double _angle, RGB _colour, Point _point);
    void set_colour(const RGB _colour);
    RGB get_colour();
    void set_cntr(const Point cntr);
    Point get_cntr();
    int get_id();
    double get_angle();
    static int counter;
    void move(const Point p);
    void rotate(int _angle);
    friend std::ostream& operator<<(std::ostream& out, Shape& shape);
    virtual void scale(int k) = 0;
    virtual double area() = 0;
    virtual ~Shape();
};

#endif // SHAPE_H
