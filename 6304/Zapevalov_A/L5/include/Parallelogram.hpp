#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP

#include "shape.hpp"

class Parallelogram : public Shape
{
public:
	Parallelogram(Point curA = Point(), Point curB = Point(), Point curC = Point(), Point curD = Point())
		: a(curA), b(curB), c(curC), d(curD)
	{
		center = calculateCenter();
		a -= center;
		b -= center;
		c -= center;
		d -= center;
	}
	bool isParallelogram()
	{
		return ((a - b) == (c - d));
	}
	Point getPointA()
	{
		return getAnyPoint(a);
	}
	Point getPointB()
	{
		return getAnyPoint(b);
	}
	Point getPointC()
	{
		return getAnyPoint(c);
	}
	Point getPointD()
	{
		return getAnyPoint(d);
	}
	Point getFourthPoint(Point a, Point b, Point c)
	{
		Point tmpCenter = (a + b)/2;
		return 2*tmpCenter - c;
	}
	double square()
	{
		return ((a.x - c.x)*(b.y - c.y) - (b.x - c.x)*(a.y - c.y));
	}

protected:
	Point calculateCenter()
	{
		center = (a + b + c + d) / 4;
		return center;
	}
	Point a;
	Point b;
	Point c;
	Point d;
};

#endif
