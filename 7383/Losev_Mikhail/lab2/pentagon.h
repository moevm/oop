#pragma once

#include <iostream>

#include "polygon.h"


class Pentagon : public Polygon
{
private:
	
public:
	Pentagon();
	Pentagon(Point, Point);
	std::ostream& print(std::ostream&) const;

	~Pentagon();
};