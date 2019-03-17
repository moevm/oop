#ifndef ELLIPS_H
#define ELLIPS_H
#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(const Point O, double a, double b, const RGB _colour);
    void scale(int k) override;
    double area() override;

    double get_radius1();
    double get_radius2();
    friend std::ostream& operator<<(std::ostream& out, Ellipse& ellipse);
protected:
    double radius1;
    double radius2;
};

#endif // ELLIPS_H
