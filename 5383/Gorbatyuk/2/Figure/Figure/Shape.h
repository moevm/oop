#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "math.h"
#include <string>
#include <iostream>

using namespace std;
struct CS
{
	double x;
	double y;
};

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color(char _r, char _g, char _b) {
		r = _r;
		g = _g;
		b = _b;
	}
	~Color();
	Color();
};

class Shape
{
protected:
	static int counter;
	int id;
	CS center;
	Color currentColor;
private:
	
public:
	Shape(Color _color);
	virtual ~Shape();
	virtual ostream &put(ostream& out) const = 0;
	virtual void Move(double _x, double _y);
	virtual void Rotate(double _angle);
	virtual void Scale(double _scale);
	virtual bool IsInsideOfAnother(const Shape& other);
};
#endif