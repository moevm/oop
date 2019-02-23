// LR2.cpp : Defines the entry point for the console application.
//
// Variant 19
#include "stdafx.h"
#include <iostream>
#include <sstream>
class Color {
	char r, g, b;
	Color(char vr, char vg, char vb) :r(vr), g(vg), b(vb) {}
	friend std::ostream& operator<< (std::ostream& stream, const Color& color) {
		return stream << "Color(" <<r<<"," << g << "," << b << ")";
	}
};
class Shape {
protected:
	double x;
	double y;
	double angle;
	Color color;
public:
	virtual void move(double x, double y) {
		this->x = x;
		this->y = y;
	}
	virtual void rotate(double angle) {
		this->angle += angle;
	}
	virtual void scale(double sc) = 0;

	virtual std::string toString() const = 0;

	friend std::ostream& operator<< (std::ostream& stream, const Shape& shape) {
		return stream << shape.toString();
	}
};

class Circle : public Shape {
protected:
	double R;
public:
	virtual void scale(double sc) {
		this->R *= sc;
	}

	virtual std::string toString() const {
		std::stringstream ss;
		ss << "Circle: x = " << x << "; y = " << y << "; angle = " << angle << "; color = " << color << "; R = " << R << std::endl;
		return ss.str();
	}
};

class Hexagon :public Shape {
protected:
	double R;
public:
	virtual void scale(double sc) {
		this->R *= sc;
	}

	virtual std::string toString() const {
		std::stringstream ss;
		ss << "Hexagon: x = " << x << "; y = " << y << "; angle = " << angle << "; color = " << color << "; R = " << R << std::endl;
		return ss.str();
	}
};
class Parallelogram :public Shape {
protected:
	double b;
	double h;
	double alpha;
public:
	virtual void scale(double sc) {
		b *= sc;
		h *= sc;
	}

	virtual std::string toString() const {
		std::stringstream ss;
		ss << "Parallelogram: x = " << x << "; y = " << y << "; angle = " << angle << "; color = " << color << "; Side = " << b << "; Height = " << h << "; Alpha = " << alpha << std::endl;
		return ss.str();
	}
};

int main()
{
	return 0;
}

