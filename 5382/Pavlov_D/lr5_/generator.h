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
Square generate_Square(long int limit)
{
	
	srand(time(0));
	Point generatePoint1 = generate_Point(50);
	double sideSize = rand() % limit + 1;
	Square shape({generatePoint1,Point(generatePoint1.getX(),generatePoint1.getY()+sideSize),
		Point(generatePoint1.getX()+sideSize,generatePoint1.getY()),Point(generatePoint1.getX() + sideSize,generatePoint1.getY()+sideSize) });
	return shape;
}
IsoscelesTriangle generate_IsoscelesTriangle(long int limit)
{
	srand(time(0));
	Point generatePoint1 = generate_Point(limit);
	double distance = rand() % (limit / 2) + 1;
	double height = rand() % (limit / 2) + 4;
	IsoscelesTriangle shape({ generatePoint1,Point(generatePoint1.getX()+height,generatePoint1.getY()+distance),
		Point(generatePoint1.getX() + height,generatePoint1.getY() - distance) });
	return shape;
}
RightTriangle generat_RightTriangle(long int limit)
{
	Point generatePoint1 = generate_Point(limit);
	RightTriangle shape({generatePoint1,Point(generatePoint1.getX(),rand()%limit),Point(rand()%limit,generatePoint1.getY())});
	return shape;
}
 void generateRandom(Shape &someFigure)
{

}