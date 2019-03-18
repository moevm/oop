#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "point.h"
#include "color.h"

class Shape
{
private:
	static unsigned int count;
	int id;

protected:
	Point centre;
	color clr;

	Shape();
	Shape(Point);
	Shape(color);
	Shape(Point, color); 
	
public:
	color get_color() const;
	void set_color(color);
 	int get_id() const;

	//Pure-virtual functions:
	virtual void move(Point) = 0;
	virtual void rotate(Point, double) = 0;
	virtual void scale(double) = 0;
	virtual std::ostream & print(std::ostream&) const = 0;

	//Virtual functions:
	virtual ~Shape();

	//Friend operators:
	friend std::ostream& operator<<(std::ostream&, const Shape&);

};