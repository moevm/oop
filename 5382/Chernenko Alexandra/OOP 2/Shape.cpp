#include "stdafx.h"
#include "Shape.h"
int Shape::ID = 0;
Shape::~Shape(){
	delete[]Tops;

}
void Shape::MoveFigure(double dx, double dy) {

	X = X + dx;
	Y = Y + dy;
};
void Shape::TurnFigure(int angle) {

	Angle = angle;
}
void Shape::ScaleFigure(double scale) {

	Scale = scale;
}
string  Shape::getColorFigure() const {

	return Color;
}
void Shape::setColorFigure(string color) {

	Color = color;
}
void  Shape::setAngle(int angle) {
	Angle = angle;
}
int  Shape::getAngle()const {
	return Angle;
}
void  Shape::setScale(double scale) {
	Scale = scale;
}
double  Shape::getScale()const {
	return Scale;
}
void  Shape::setId(int id) {
	Id = id;
}
int  Shape::getId() const {
	return Id;
}
double  Shape::getX() const {
	return X;
}
double  Shape::getY()const {
	return Y;
}
void Shape::setPoints(Point*temp){
	Tops = temp;
}
Point* Shape::getPoints()const{
	return Tops;
}
double Shape::getKoeff()const{
	return koeff;
}
void Shape::outPoint(ostream& a,int b)const{
	Point *p = getPoints();
	for (int i = 0; i < b; i++){
		a << "Точка " << i + 1 << " :x= " << p[i].getX() << " ,y= " << p[i].getY() << "\n";
	}

}
void Shape::setType(int Type){
	type = Type;
}
int Shape::getType()const{
	return type;
}
bool Shape::hasCommonSide(const Shape& other){
	int q1, q2;
	if (type == 0){
		q1 = 4;
	}
	else{
		q1 = 5;
	}
	if (other.type == 0){
		q2 = 4;
	}
	else{
		q2 = 5;
	}
	if (getType() == 0){
		for (int i = 0; i < q2; i++){
			for (int j = 0; j < q1; j++){
				if (other.Tops[i].getX() == Tops[j].getX() && other.Tops[i].getY() == Tops[j].getY()){
					if (other.Tops[(i + 1) % 4].getX() == Tops[(j + 1) % 4].getX() && other.Tops[(i + 1) % 4].getY() == Tops[(j + 1) % 4].getY()) return true;
					if (other.Tops[(i - 1) % 4].getX() == Tops[(j - 1) % 4].getX() && other.Tops[(i - 1) % 4].getY() == Tops[(j - 1) % 4].getY()) return true;
					if (other.Tops[(i - 1) % 4].getX() == Tops[(j + 1) % 4].getX() && other.Tops[(i - 1) % 4].getY() == Tops[(j + 1) % 4].getY()) return true;
					if (other.Tops[(i + 1) % 4].getX() == Tops[(j - 1) % 4].getX() && other.Tops[(i + 1) % 4].getY() == Tops[(j - 1) % 4].getY()) return true;
				}
			}
		}
	}
	else{
		for (int i = 0; i < q2; i++){
			for (int j = 0; j <q1; j++){
				if (other.Tops[i].getX() == Tops[j].getX() && other.Tops[i].getY() == Tops[j].getY()){
					if (other.Tops[(i + 1) % 4].getX() == Tops[(j + 1) % 4].getX() && other.Tops[(i + 1) % 4].getY() == Tops[(j + 1) % 4].getY()) return true;
					if (other.Tops[(i - 1) % 4].getX() == Tops[(j - 1) % 4].getX() && other.Tops[(i - 1) % 4].getY() == Tops[(j - 1) % 4].getY()) return true;
					if (other.Tops[(i - 1) % 4].getX() == Tops[(j + 1) % 4].getX() && other.Tops[(i - 1) % 4].getY() == Tops[(j + 1) % 4].getY()) return true;
					if (other.Tops[(i + 1) % 4].getX() == Tops[(j - 1) % 4].getX() && other.Tops[(i + 1) % 4].getY() == Tops[(j - 1) % 4].getY()) return true;
				}
			}
		}
	}
	return false;
}