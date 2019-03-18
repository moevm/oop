#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "shape.h"


class Polygon : public Shape
{
private:

protected:
	int ver_num;
	Point *p_vertexes;


	void set_ver_num(int);
	
	void set_center(Point);
	void set_vertexes(Point);

public:
	Polygon();
	Polygon(Point, Point);

	int get_ver_num() const;
	Point get_center() const;

	virtual void rotate(Point, double);
	virtual void move(Point);
	virtual void scale(double);

	virtual std::ostream & print_info(std::ostream&) const;
	virtual std::ostream & print(std::ostream&) const;

	~Polygon();
};