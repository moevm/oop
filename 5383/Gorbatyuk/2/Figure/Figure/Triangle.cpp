#include "stdafx.h"
#include "Triangle.h"

#define PI 3.14159265  

Triangle::Triangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
	this->a.x = _ax;
	this->a.y = _ay;
	this->b.x = _bx;
	this->b.y = _by;
	this->c.x = _cx;
	this->c.y = _cy;
}

void Triangle::Move(double _x, double _y)
{
	CS center;
	center.x = (this->a.x + this->b.x + this->c.x) / 3;
	center.y = (this->a.y + this->b.y + this->c.y) / 3;
	this->a.x += _x - center.x;
	this->a.y += _y - center.y;
	this->b.x += _x - center.x;
	this->b.y += _y - center.y;
	this->c.x += _x - center.x;
	this->c.y += _y - center.y;
}


void Triangle::Rotate(double _angle)
{
	CS center;
	center.x = (this->a.x + this->b.x + this->c.x) / 3;
	center.y = (this->a.y + this->b.y + this->c.y) / 3;
	this->a.x = center.x + (this->a.x - center.x) * cos(_angle * PI / 180) - (this->a.y - center.y) * sin(_angle * PI / 180);
	this->a.y = center.y + (this->a.x - center.x) * sin(_angle * PI / 180) + (this->a.y - center.y) * cos(_angle * PI / 180);
	this->b.x = center.x + (this->b.x - center.x) * cos(_angle * PI / 180) - (this->b.y - center.y) * sin(_angle * PI / 180);
	this->b.y = center.y + (this->b.x - center.x) * sin(_angle * PI / 180) + (this->b.y - center.y) * cos(_angle * PI / 180);
	this->c.x = center.x + (this->c.x - center.x) * cos(_angle * PI / 180) - (this->c.y - center.y) * sin(_angle * PI / 180);
	this->c.y = center.y + (this->c.x - center.x) * sin(_angle * PI / 180) + (this->c.y - center.y) * cos(_angle * PI / 180);
}

void Triangle::Scale(double _scale)
{
	CS center;
	center.x = (this->a.x + this->b.x + this->c.x) / 3;
	center.y = (this->a.y + this->b.y + this->c.y) / 3;
	this->a.x = center.x + (this->a.x - center.x) * _scale;
	this->a.y = center.y + (this->a.y - center.y) * _scale;
	this->b.x = center.x + (this->b.x - center.x) * _scale;
	this->b.y = center.y + (this->b.y - center.y) * _scale;
	this->c.x = center.x + (this->c.x - center.x) * _scale;
	this->c.y = center.y + (this->c.y - center.y) * _scale;
}

void Triangle::SetColor(string _color)
{
	this->color = _color;
}

string Triangle::GetColor()
{
	return this->color;
}


ostream &Triangle::put(ostream &out) const
{
	return out << "This is triangle" << endl << "Point's coordinates: " << endl << "x1 | " << this->a.x << " y1 | " << this->a.y << endl << "x2 | " << this->b.x << " y2 | " << this->b.y << endl << "x3 | " << this->c.x << " y3 | " << this->c.y << endl;
}


Triangle::~Triangle()
{
}

ostream & operator<<(ostream &out, Shape & a)
{
	return a.put(out);
}
