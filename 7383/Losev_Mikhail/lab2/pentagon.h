#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "shape.h"


class Pentagon : public Shape
{
private:
	Point vertex; // правильный пятиугольник определяется серединой и одним из углов

public:
	Pentagon();
	Pentagon(Point, Point);

	void rotate(Point, double);
	void move(Point);
	void scale(double);

	~Pentagon();
	friend std::ostream& operator<<(std::ostream&, const Pentagon&);
};