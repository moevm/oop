#include "shape.h"

unsigned Shape::id = 0;
std::string const Shape::defaultColor = "white";

std::ostream& operator<<(std::ostream& out, const Parallelogram& parallelogram){
    out << "COLOR: " << parallelogram.color << std::endl;
    out << "ID: " << parallelogram.id << std::endl;
    out << "CENTRE: " << parallelogram.centre << "Point 1: " << parallelogram.point1 << "Point 2: " << parallelogram.point2;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Point& point){
    out << "Point X: " << point.x << " Point Y: " << point.y << std::endl;
    return out;
}

Parallelogram::Parallelogram(Point centre = Point(0, 0), Point point1 = Point(0, 0), Point point2 = Point(0, 0), std::string color = defaultColor)
            : id(Shape::id), centre(centre), point1(point1), point2(point2){
    this->color = color;
}

Parallelogram::Parallelogram(): id(Shape::id){
    this->color = defaultColor;
}

void Parallelogram::changeCoordinate(Point newCentre, Point newPoint1, Point newPoint2){ // аргументы по умолчанию?
    centre = newCentre;
    point1 = newPoint1;
    point2 = newPoint2;
}

void Parallelogram::multiplicateCoordinate(unsigned k = 1){
    point1.x = centre.x + (point1.x - centre.x) * k;
    point1.y = centre.y + (point1.y - centre.y) * k;
    point2.x = centre.x + (point2.x - centre.x) * k;
    point2.y = centre.y + (point2.y - centre.y) * k;
}

void Parallelogram::rotate(double angle){
    point1.x = pow(point1.x - centre.x, 2) * cos(angle);
    point1.y = pow(point1.y - centre.y, 2) * sin(angle);
    point2.x = pow(point2.x - centre.x, 2) * cos(angle);
    point2.y = pow(point2.y - centre.y, 2) * sin(angle);
}





