#include <iostream>
#include "cmath"

#include "point.h"

Point::Point() { }

Point::Point(int x, int y) : x(x), y(y) { }
Point::~Point() { }


double Point::get_x() const { return x; }
double Point::get_y() const { return y; }

void Point::set_x(double _x) { x = _x; }
void Point::set_y(double _y) { y = _y; }


void Point::rotate(Point cntr, double ang)
{
	double tmpx = x;
	x = cntr.get_x() + (x - cntr.get_x()) * cos(ang) + (y - cntr.get_y()) * sin(ang); // формула для поворота точки на угол в координатах
	y = cntr.get_y() + (tmpx - cntr.get_x()) * sin(ang) + (y - cntr.get_y()) * cos(ang);
} 

void Point::move(Point p)
{
	x = p.get_x();
	y = p.get_y();
}


Point Point::operator+(Point& b) {
	return Point(this->x + b.get_x(), this->y + b.get_y());
}
Point Point::operator-(Point& b) {
	return Point(this->x - b.get_x(), this->y - b.get_y());
}



/*

Point Point::operator*(const double b) {
	return *Point(this->x * b, this->y * b);
}*/

std::ostream& operator<<(std::ostream& out, const Point& obj)
{
	out << "Points coorditates: (" << obj.x << ", " << obj.y << ")\n";

	//out << std::endl;

	return out;
}