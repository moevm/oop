#ifndef LAB2_PARALLELOGRAM_H
#define LAB2_PARALLELOGRAM_H

#include <vector>
#include <cmath>
#include "Shape.h"

class Parallelogram: public Shape{
    std::vector<Point> pts;
public:
    // по смежным сторонам и углу
    Parallelogram(std::string color,double angle, double a, double b);
    void applyForAnyPoint(std::function<void(Point&)> const & f) override ;
    std::string toString() const override ;
protected:
    explicit Parallelogram(std::string color);
};
#endif //LAB2_PARALLELOGRAM_H
