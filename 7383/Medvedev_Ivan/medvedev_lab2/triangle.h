#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"


class Triangle : public Shape
{
public:
    Triangle();
    Triangle(const Point A, const Point B, const Point C, const RGB _colour);
    void scale(int k) override;
    double area () override;
    void calculation_sides(Point A, Point B, Point C);
    friend std::ostream& operator<<(std::ostream& out, Triangle& triangle);
    ~Triangle() override;


protected:
    std::vector <double> sides;
};

#endif // TRIANGLE_H
