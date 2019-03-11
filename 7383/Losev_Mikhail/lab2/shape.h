#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "point.h"
#include "color.h"

class Shape
{
private:
	static unsigned int count;
	int id;
	
	//Pure-virtual (non-used) functions:
	//virtual void set_crd() = 0;

protected:
	Point centre;
	color clr;

	Shape();
	Shape(Point);
	Shape(color);
	Shape(Point centre, color clr); 
	virtual ~Shape();

public:
	

	color get_color() const;
	void set_color(color);
 	int get_id() const;

	//Pure-virtual functions:
	virtual void move(Point) = 0;
	virtual void rotate(Point, double) = 0;
	virtual void scale(double) = 0;

	//Virtual functions:
	
	//Friend operators:
	friend std::ostream& operator<<(std::ostream&, const Shape&);
};