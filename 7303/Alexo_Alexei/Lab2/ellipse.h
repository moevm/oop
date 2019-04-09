#ifndef ELIPSE_H
#define ELIPSE_H

#include <vector>
#include "shape.h"

class Ellipse: public Shape{
public:
    Ellipse(Color color, Point center, double smallRadius, double bigRadius);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const Ellipse& ellipse);
    friend void operator * (Ellipse& ellipse, double coefficient);
    friend void operator + (Ellipse& ellipse, double distance);
private:
    double smallRadius;
    double bigRadius;
};

#endif // ELIPSE_H
