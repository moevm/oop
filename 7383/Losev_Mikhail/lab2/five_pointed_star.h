#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "shape.h"
#include "polygon.h"


class FivePointedStar : public Polygon
{
private:
	Point *p_inner_vertexes;
	int inner_ver_num;

public:
	FivePointedStar();
	FivePointedStar(Point, Point);
	
	void set_inner_vertexes(Point);

	void rotate(Point, double);
	void move(Point);
	void scale(double);
	std::ostream& print(std::ostream&) const;

	~FivePointedStar();
	//friend std::ostream& operator<<(std::ostream&, const FivePointedStar&);
};