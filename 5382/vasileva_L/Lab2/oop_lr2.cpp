
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include "gtest/gtest.h"
#include "oop_lr2.h"

using namespace std;

const string str[6] = { "transparent", "red", "yellow", "blue", "white", "black" };

Shape::Shape()
{
	color = 0;
}

int Shape::getId()
{
	return id;
}


void Shape::Move(float x_, float y_)  
{
	for (int i = 0; i < x.size(); i++)
	{
		x[i] += x_;
		y[i] += y_;
	}	
}

void Shape::Rotate(float alpha)        //поворот фигуры относительно начала координат
{
	for (int i = 0; i < x.size(); i++)
	{
		float x_ = x[i] * cos(alpha) - y[i] * sin(alpha);
		float y_ = x[i] * sin(alpha) + y[i] * cos(alpha);
		x[i] = x_;
		y[i] = y_;
	}
}

void Shape::setColor(unsigned color_)
{
	if (color_ > 5)
		throw std::invalid_argument("It's not such color!");
	color = color_;
}

void Shape::getColor()
{
	cout << "Color of the figure is " << str[color] << "\n";
}

ostream& operator<< (ostream& s, const Shape& shape_)
{
	return shape_.put(s);
}

Ellipse::Ellipse(float xc, float yc, float r1_, float r2_)
{
	if ((r1_ <= 0) || (r2_ <= 0))
		throw std::invalid_argument("Radius must be positive");
	id = 1;	
	r1 = r1_;
	r2 = r2_;
	x.push_back(xc);
	y.push_back(yc);
}

void Ellipse::Scale(float k) 
{
	if (k <= 0)
		throw std::invalid_argument("Coefficient of scale must be positive");
	r1 *= k;
	r2 *= k;
}

ostream& Ellipse::put(ostream& out) const
{
	out << "The figure is ellipse\nwith center in coordinates\n("
		<< x[0] << "; " << y[0] << ")\n"
		<< "and radius are r1 = " << r1 << "   r2 = " << r2 << "\n"
		<< "color is " << str[color] << "\n\n";
	return out;
}

Trapezium::Trapezium(float topLeft_x, float topLeft_y, float bottomLeft_x, float bottomLeft_y, float topBase_, float bottomBase_)
{
	if ((topLeft_x == bottomLeft_x) && (topLeft_y == bottomLeft_y))
		throw std::invalid_argument("There is not distance between coordinates of left side of trapezium");
	if ((topBase_ <= 0) || (bottomBase_ <= 0))
		throw std::invalid_argument("Bases of trapezium must be positive");
	id = 2;	
	outputIsolated = " ";
	topBase = topBase_; bottomBase = bottomBase_;
	x.push_back(topLeft_x);
	y.push_back(topLeft_y);
	x.push_back(bottomLeft_x);
	y.push_back(bottomLeft_y);
	x.push_back(topLeft_x + topBase);
	y.push_back(topLeft_y);
	x.push_back(bottomLeft_x + bottomBase);
	y.push_back(bottomLeft_y);
}

void Trapezium::Scale(float k)   
{
	if (k <= 0)
		throw std::invalid_argument("Coefficient of scale must be positive");
	for (int i = 1; i < x.size(); i++)
	{
		x[i] = x[0] + abs((x[i] - x[0]))*k;
		y[i] = y[0] + abs((y[i] - y[0]))*k;
	}
	topBase *= k; bottomBase *= k;
}

ostream& Trapezium::put(ostream& out) const
{
	out << "The figure is" << outputIsolated << "trapezium\nwith coordinates\n";
	for (int i = 0; i < x.size(); i++)
		out << "(" << x[i] << "; " << y[i] << ")\n";
	out << "length of basis are top_base = " << topBase << "   bottom_base = " << bottomBase
		<< "\ncolor is " << str[color] << "\n\n";
	return out;
}

IsoscelesTrapezium::IsoscelesTrapezium(float topLeft_x, float topLeft_y, float bottomLeft_x, float bottomLeft_y, float bottomBase) :
		Trapezium(topLeft_x, topLeft_y, bottomLeft_x, bottomLeft_y, -2 * topLeft_x + bottomBase + 2 * bottomLeft_x, bottomBase)
{
	id = 3;
	outputIsolated = " isosceles ";
}


/*int main()
{
	//shape* shape = new trapezium(1,1,2,2,3,4);
	//cout << *shape;
	//delete shape;

	IsoscelesTrapezium is(-2, 4, -1, 1, 5);
	cout << is.getId();
	return 0;
}*/
