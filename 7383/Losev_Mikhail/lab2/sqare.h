#pragma once

#include <iostream>

#include "polygon.h"


class Sqare : public Polygon
{
private:
	
public:
	Sqare();
	Sqare(Point, Point);

	std::ostream& print(std::ostream&) const;

	~Sqare();
};