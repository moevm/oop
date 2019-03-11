#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"


class Triangle : public Shape
{
public:
    Triangle();
    Triangle(const Point A, const Point B, const Point C, const RGB _colour);
    void move(const Point p) override;
    void scale(int k) override;
    void rotate(int _angle) override;
    double area () override;
    friend std::ostream& operator<<(std::ostream& out, Triangle& triangle);
    ~Triangle() override;


protected:
    std::vector <Point> points;
    std::vector <double> sides;
};

#endif // TRIANGLE_H
