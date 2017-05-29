#ifndef PENTAGON_H
#define PENTAGON_H
#include "shape.h"
#include "point.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Pentagon : public Shape {//класс - пятиугольничек
protected:

	//Point TCenter;
	//Point right_bottom;
	//Point left_bottom;
	//Point left_top;
	//Point right_top;
	//std::vector<Point> vertex1;

	
public:
	Pentagon(Point current_center, int angle, double scale, vector <Point> vertex);
	void Pentagon::move(Point new_center) override;
	virtual void Scale(double scale) override;
	void print(ostream &ost) override;
	void rotate(int new_center) override;
	~Pentagon() {};
};
#endif// PENTAGON_H