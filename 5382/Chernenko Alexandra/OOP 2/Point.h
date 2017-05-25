#pragma once
#include "stdafx.h"
class Point{
private:
	double x, y;
public:
	Point();
	Point(double, double);
	void setCoord(double, double);
	void setX(double);
	void setY(double);
	double* getCoord();
	double getX();
	double getY();
	~Point();

};
