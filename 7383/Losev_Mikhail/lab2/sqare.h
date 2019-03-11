#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "shape.h"


class Sqare : public Shape
{
private:
	Point vertex; // квадрат определяется серединой и одним из углов

public:
	Sqare();
	Sqare(Point, Point);

	void rotate(Point, double);
	void move(Point);
	void scale(double);

	~Sqare();
	friend std::ostream& operator<<(std::ostream&, const Sqare&);
};