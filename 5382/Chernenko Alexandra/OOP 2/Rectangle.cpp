#include "stdafx.h"
#include "Rectangle.h"
Rectangle::Rectangle(double y, double x, double side1, double side2, double scale, int angle, string color) :SideX(side1), SideY(side2) {

	MoveFigure(x, y);
	setColorFigure(color);
	setAngle(angle);
	setScale(scale);
	setId(ID);
	setType(0);
	init();
	ID++;
};
Rectangle::Rectangle(double side1, double side2) :SideX(side1), SideY(side2) {

	setId(ID);
	init();
	ID++;
};

Rectangle::~Rectangle(){

};

void Rectangle::init(){
	Point *point = new Point[4];
	double tempX, tempY;
	double R=sqrt(SideX*SideX+SideY*SideY)/2*getScale();
	startAngle = atan(SideY / SideX) + getAngle() * getKoeff();
	tempX = R * cos(startAngle)+getX() ;
	tempY = R * sin(startAngle) + getY();
	tempX = round(tempX * 1000) / 1000;
	tempY = round(tempY * 1000) / 1000;
	point[0].setCoord(tempX, tempY);
	startAngle += (M_PI - 2 * atan(SideY/ SideX));
	tempX = R * cos(startAngle) + getX();
	tempY = R * sin(startAngle) + getY();
	tempX = round(tempX * 1000) / 1000;
	tempY = round(tempY * 1000) / 1000;
	point[1].setCoord(tempX, tempY);
	startAngle += M_PI - (2 * atan(SideX / SideY));
	tempX = R * cos(startAngle) + getX();
	tempY = R * sin(startAngle) + getY();
	tempX = round(tempX * 1000) / 1000;
	tempY = round(tempY * 1000) / 1000;
	point[2].setCoord(tempX, tempY);
	startAngle +=( M_PI - 2 * atan(SideY / SideX));
	tempX = R * cos(startAngle) + getX();
	tempY = R * sin(startAngle) + getY();
	tempX = round(tempX * 1000) / 1000;
	tempY = round(tempY * 1000) / 1000;
	point[3].setCoord(tempX, tempY);
	setPoints(point);
}
