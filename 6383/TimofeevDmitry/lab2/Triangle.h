#ifndef LAB2_TRIANGLE_H
#define LAB2_TRIANGLE_H

#include <vector>
#include "Shape.h"

class Triangle: public Shape{
    std::vector<Point> pts;
public:
    Triangle(std::string color,const Point& a,const Point& b, const Point& c);
    void applyForAnyPoint(std::function<void(Point&)> const & f) override;
    std::string toString() const override ;
};
#endif //LAB2_TRIANGLE_H
