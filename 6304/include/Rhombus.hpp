#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP
#include "Parallelogram.hpp"
class Rhombus : public Parallelogram
{
public:
	Rhombus(Point curA = Point(), Point curB = Point(), Point curC = Point(), Point curD = Point())
		: Parallelogram(curA, curB, curC, curD)
	{

	}
	Point getThirdPoint(Point a, Point b)
	{
		Point tmpCenter = (a - b)/2;
		double normieK = -(b.y - a.y) / (b.x - a.x);
		double normieB = normieK * a.x - a.y;
		Point tmp = getRandomPoint();
		Point c(tmp.x, normieK*tmp.x + normieB);
		return c;
	}
	bool isRhombus()
	{
		return (sqrt((a - b).x * (a - b).x + (a - b).y * (a - b).y) == sqrt((a - d).x * (a - d).x + (a - d).y * (a - d).y) && isParallelogram());
	}
};
#endif