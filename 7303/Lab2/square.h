#ifndef SQUARE_H
#define SQUARE_H

#include "point.h"
#include "shape.h"
#include <vector>
using namespace std;

class Square:public Shape{
public:
    Square(Color color, Point center, double lenght);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const Square& square);
    friend void operator * (Square& square, double coefficient);
    friend void operator + (Square& square, double distance);
private:
    double lenght;
};

#endif // SQUARE_H
