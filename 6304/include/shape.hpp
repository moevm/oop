#ifndef shape_hpp
#define shape_hpp
#include <cmath>
#include <iostream>
#include <string.h>
#define M_PI 3.14159265358979323846

using namespace std;

class Point
{
public:
	Point(double curX = 0, double curY = 0) : x(curX), y(curY)
	{

	}

	Point(const Point& setPoint) : x(setPoint.x), y(setPoint.y)
	{

	}

	friend ostream& operator<< (ostream & os, const Point & p)
	{
		os << "(" << p.x << "," << p.y << ")";
		return os;
	}

	Point* operator+= (const Point& m)
	{
		x += m.x;
		y += m.y;
		return this;
	}
	Point* operator-= (const Point& m)
	{
		x -= m.x;
		y -= m.y;
		return this;
	}
	Point* operator= (const Point& t)
	{
		x = t.x;
		y = t.y;
		return this;
	}
	Point getRandomPoint(){
    	Point p;
    	p.x = rand() / (float)RAND_MAX * 1000;
    	p.y = rand() / (float)RAND_MAX * 1000;
    	return p;
	}
	Point* turnByAngle(double curAngle)
	{
		if (curAngle)
		{
			double R = getR();
			double angle = getPhi() + curAngle;
			setPhi(angle);
		}
		return this;
	}
	double getR()
	{
		return sqrt(x * x + y * y);
	}
	double getPhi()
	{
		if ((x == 0) && (y > 0)) return M_PI / 2;
		if ((x == 0) && (y < 0)) return 3*M_PI / 2;
		if ((x > 0) && (y >= 0)) return atan(y / x);
		if ((x > 0) && (y < 0)) return atan(y / x) + 2*M_PI;
		if (x < 0) return atan(y / x) + M_PI;
		return 0;
	}
	void setR(double R) {
		double Phi = getPhi();
		x = R * cos(Phi);
		y = R * sin(Phi);
	}
	void setPhi(double Phi) {
		double R = getR();
		x = R * cos(Phi);
		y = R * sin(Phi);
	}
	double x;
	double y;
};

Point operator+ (const Point& a, const Point& b)
{
	Point p;
	p.x = a.x + b.x;
	p.y = a.y + b.y;
	return p;
}


Point operator- (const Point& a, const Point& b)
{
	Point p;
	p.x = a.x - b.x;
	p.y = a.y - b.y;
	return p;
}

Point operator/ (const Point& a, double divider)
{
	Point b = a;
	b.x /= divider;
	b.y /= divider;
	return b;
}


Point operator* (const Point& a, double divider)
{
	Point b = a;
	b.x *= divider;
	b.y *= divider;
	return b;
}

bool operator== (const Point& a, const Point& b)
{
	return ((a.x == b.x) && (a.y == b.y));
}

class Shape
{
public:
	void setColor(unsigned int curColor)
	{
		color = curColor;
	}
	unsigned int getColor()
	{
		return color;
	}
	void printColor()
	{
		if (color <= 15)
			cout << "0x00000" << hex << color;
		if (color > 15 && color <= 255)
			cout << "0x0000" << hex << color;
		if (color > 255 && color <= 4095)
			cout << "0x000" << hex << color;
		if (color > 4095 && color <= 65535)
			cout << "0x00" << hex << color;
		if (color > 65535 && color <= 1048575)
			cout << "0x0" << hex << color;
		if (color > 1048575 && color <= 16777215)
			cout << "0x" << hex << color;
		if (color > 16777215)
			cout << "Undefined color";
		cout << "\n";
	}
	Point getCenter()
	{
		return center;
	}
	void virtual turnAround(double curAngle)
	{
		angle = curAngle;
	}
	virtual void moveByDelta(Point delta)
	{
		center += delta;
	}
	void virtual resize(double curMultiplier)
	{
		multiplier = curMultiplier;
	}
	void setCenter(Point s)
	{
		center = s;
	}
	virtual double square()
	{
		return 0;
	}
	Shape() {
		multiplier = 1;
		angle = 0;
	}
	virtual ~Shape() = default;

protected:
	Point getAnyPoint(Point curPoint)
	{
		Point t = curPoint;
		t = t * multiplier;
		t.turnByAngle(angle);
		t += center;
		return t;
	}
	unsigned int color;
	double multiplier;
	double angle;
	Point center;
};


#endif