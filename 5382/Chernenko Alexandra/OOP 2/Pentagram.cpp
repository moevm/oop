#include "stdafx.h"
#include "Pentagram.h"
Pentagram::Pentagram(double y, double x, double side, double scale, int angle, string color) :Side(side) {

	MoveFigure(x, y);
	setColorFigure(color);
	setAngle(angle);
	setScale(scale);
	setId(ID);
	init();
	setType(2);
	ID++;
};
Pentagram::Pentagram(double side) :Side(side) {

	setId(ID);
	ID++;
};


Pentagram::~Pentagram(){

};
void Pentagram::init(){
	Point *point = new Point[5];
	double R = Side/sqrt(2-2*cos(144*getKoeff())) * getScale();
	for (int i = 0; i < 5; i++){
		double tempX, tempY;
		tempX = R * cos((90 + 144 * i + getAngle()) * getKoeff())+getX();
		tempY = R * sin((90 + 144 * i + getAngle()) * getKoeff())+getY();
		tempX = round(tempX * 1000) / 1000;
		tempY = round(tempY * 1000) / 1000;
		point[i].setCoord(tempX, tempY);
	}
	setPoints(point);
}
