#ifndef Triangle_hpp
#define Triangle_hpp

#include "shape.hpp"

using namespace std;

class Triangle : public Shape
{
public:

	Triangle(Point curA = Point(), Point curB = Point(), Point curC = Point()) : a(curA), b(curB), c(curC)
	{
		center = calculateCanter();
		a -= center;
		b -= center;
		c -= center;
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
	double square()
	{
		return ((a.x - c.x)*(b.y - c.y) - (b.x - c.x)*(a.y - c.y)) / 2;
	}

private:
	Point calculateCanter() {
		center = (a + b + c) / 3;
		return center;
	}
	Point a;
	Point b;
	Point c;
};
#endif // !Triangle.hpp