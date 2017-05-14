#include "stdafx.h"
#include "Shape.h"

#define PI 3.14159265  

int Shape::counter = 0;

Shape::Shape(Color _color)
{
	this->currentColor = _color;
	id = counter++;
}


Shape::~Shape()
{
}


void Shape::Move(double _x, double _y)
{
}

void Shape::Rotate(double _angle)
{
}

void Shape::Scale(double _scale)
{
}


bool Shape::IsInsideOfAnother(const Shape & other)
{
	return false;
}

Color::~Color()
{
}

Color::Color()
{
}
