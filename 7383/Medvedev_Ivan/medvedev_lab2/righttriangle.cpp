#include "righttriangle.h"

RightTriangle::RightTriangle() : Triangle (Point(0,0),Point(0,5),Point(5,0), RGB()){}

RightTriangle::RightTriangle(const Point A, double a, double b, const RGB _colour):Triangle(Point(A.x, A.y+a), A, Point(A.x+b, A.y), _colour){}

std::ostream& operator<<(std::ostream& out, RightTriangle& rtriangle){
    out << (Triangle&)rtriangle;
    return out;
}
