#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "shape.h"


class FivePointedStar : public Shape
{
private:
	Point vertex; // пятиконечная звезда определяется серединой и одним из углов (в силу своей симметричности)

public:
	FivePointedStar();
	FivePointedStar(Point, Point);
	
	void rotate(Point, double);
	void move(Point);
	void scale(double);
	
	~FivePointedStar();
	friend std::ostream& operator<<(std::ostream&, const FivePointedStar&);
};