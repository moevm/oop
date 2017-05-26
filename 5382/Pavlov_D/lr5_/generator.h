#pragma once
#include "Square.h"
#include "IsoscelesTriangle.h"
#include "RightTriangle.h"
#include <ctime>
//Simple random generator.Need More....
Point generate_Point(long int limit)
{
	srand(time(0));
	Point point(rand() % limit, rand() % limit);
	return point;
}
stepik::shared_ptr<Shape>  generate_Square(long int limit)
{

	srand(time(0));
	Point generatePoint1 = generate_Point(limit);
	double sideSize = rand() % limit + 1;
	stepik::shared_ptr<Shape> buffer(new Square({ generatePoint1,Point(generatePoint1.getX(),generatePoint1.getY() + sideSize),
		Point(generatePoint1.getX() + sideSize,generatePoint1.getY()),Point(generatePoint1.getX() + sideSize,generatePoint1.getY() + sideSize) }));
	return buffer;
}
stepik::shared_ptr<Shape> generate_IsoscelesTriangle(long int limit)
{
	srand(time(0));
	Point generatePoint1 = generate_Point(limit);
	double distance = rand() % (limit / 2) + 1;
	double height = rand() % (limit / 2) + 4;
	stepik::shared_ptr<Shape> buffer(new IsoscelesTriangle({ generatePoint1,Point(generatePoint1.getX() + height,generatePoint1.getY() + distance),
		Point(generatePoint1.getX() + height,generatePoint1.getY() - distance) }));
	return buffer;
}
stepik::shared_ptr<Shape> generat_RightTriangle(long int limit)
{
	Point generatePoint1 = generate_Point(limit);
	stepik::shared_ptr<Shape> buffer(new RightTriangle({ generatePoint1,
		Point(generatePoint1.getX(),rand() % limit),Point(rand() % limit,generatePoint1.getY()) }));
	return buffer;
}
