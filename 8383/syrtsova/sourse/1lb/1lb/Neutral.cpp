#include "pch.h"
#include "Neutral.h"
#include "Object.h"
#include <iostream>
#include <string>


Neutral::Neutral(char n, string message_, int x_, int y_, int col) {
	name = n; 
	object = name;
	color = col;
	//message(message_);
	XY.x = x_;
	XY.y = y_;
}

int Neutral::getX()
{
	return XY.x;
}

int Neutral::getY()
{
	return XY.y;
}

void Neutral::message(string message)
{
	std::cout << message;
}

Pab::Pab(int &x_max, int &y_max) : Neutral('P', "This is PAB!", (x_max-2), 1, colorLand::red){
	/*this->XY.x = 1;
	this->XY.y = y_max - 1;*/
}

void Pab::operator+ (Units* unit){
	// бесмысленно существует
}

Pab::~Pab() {

}

Tablet::Tablet(int &x_max, int &y_max) : Neutral('T', "This is Tablet", (x_max / 2), (y_max / 2), colorLand::cyan) {
}

void Tablet::operator+ (Units* unit){
	// бесмысленно существует
}
Tablet::~Tablet() {}


Cave::Cave(int &x_max, int &y_max) : Neutral('C', "This is Cave", (x_max), (y_max), colorLand::yellow) {
}


void Cave::operator+ (Units* unit){
	// бесмысленно существует
}

Cave::~Cave() {

}


Ruin::Ruin(int &x_max, int &y_max) : Neutral('R', "This is Ruin", (x_max / 2), (y_max - 3), colorLand::lightBlue) {
}

void Ruin::operator+ (Units* unit){
	// бесмысленно существует
}
Ruin::~Ruin() {
}
