#include "stdafx.h"
#include "shape.h"
#include "point.h"
#include <string>
#include "pentagon.h"
#include <iostream>
#include <vector>

using namespace std;

Pentagon::Pentagon(Point current_center, int angle, double scale, vector <Point> vertex)
	:Shape(current_center, angle, scale)
{//TCentr = vertex[4]
	this->vertex.resize(5);
	for (int i = 0; i <= 2; i++) {
		if ((((vertex[i].y != vertex[i+1].y) || (vertex[i].y != vertex[i+2].y) || (vertex[i + 1].y != vertex[i + 2].y))
			&& ((vertex[i].x != vertex[i + 1].x) || (vertex[i].x != vertex[i + 2].x) || (vertex[i + 1].x != vertex[i + 2].x))))
		{	
			this->vertex[i] = vertex[i];
		}
		else {
			throw std::invalid_argument("Вы построили не пятиугольник!!!");
		}
	}
}

void Pentagon::move(Point new_center)
{
	double X = new_center.x - current_center.x;
	double Y = new_center.y - current_center.y;
	for (int i = 0; i < 5; i++)
	{
		vertex[i].x += X;
		vertex[i].y += Y;
	}
}

void Pentagon::Scale(double scale)
{
	for (int i = 0; i < 5; i++)
	{
		vertex[i].x *= scale;
		vertex[i].y *= scale;
	}
}


void Pentagon::rotate(int new_angle) 
{
	double angle = new_angle;
	Point temp_left_top;
	Point temp_left_bottom;
	Point temp_right_top;
	Point temp_right_bottom;
	Point tempTCenter;
	tempTCenter.x = vertex[4].x;
	tempTCenter.y= vertex[4].y;
	temp_left_top.x = vertex[1].x;
	temp_left_bottom.x = vertex[0].x;
	temp_right_top.x = vertex[3].x;
	temp_right_bottom.x = vertex[2].x;
	temp_left_top.y = vertex[1].y;
	temp_left_bottom.y = vertex[0].y;
	temp_right_top.y = vertex[3].y;
	temp_right_bottom.y = vertex[2].y;
	
	vertex[1].x = current_center.x + (temp_left_top.x - current_center.x) * cos(angle) - (temp_left_top.y - current_center.y) * sin(angle);
	vertex[1].y = current_center.y + (temp_left_top.x - current_center.x) * sin(angle) + (temp_left_top.y - current_center.y) * cos(angle);
	vertex[3].x = current_center.x + (temp_right_top.x - current_center.x) * cos(angle) - (temp_right_top.y - current_center.y) * sin(angle);
	vertex[3].y = current_center.y + (temp_right_top.x - current_center.x) * sin(angle) + (temp_right_top.y - current_center.y) * cos(angle);
	vertex[0].x = current_center.x + (temp_left_bottom.x - current_center.x) * cos(angle) - (temp_left_bottom.y - current_center.y) * sin(angle);
	vertex[0].y = current_center.y + (temp_left_bottom.x - current_center.x) * sin(angle) + (temp_left_bottom.y - current_center.y) * cos(angle);
	vertex[2].x = current_center.x + (temp_right_bottom.x - current_center.x) * cos(angle) - (temp_right_bottom.y - current_center.y) * sin(angle);
	vertex[2].y = current_center.y + (temp_right_bottom.x - current_center.x) * sin(angle) + (temp_right_bottom.y - current_center.y) * cos(angle);
	angle += new_angle;
}
void Pentagon::print(ostream &ost)
{
	setlocale(LC_ALL, "Rus");
	ost << endl << "Пятиугольник" << endl;
	ost << endl << "Текущие координаты: " << "(" << vertex[4].x << ";" << vertex[4].y << ")" <<
											 "(" << vertex[1].x << ";" << vertex[1].y << ")" <<
											 "(" << vertex[0].x << ";" << vertex[0].y << ")" <<
											 "(" << vertex[2].x << ";" << vertex[2].y << ")" <<
											 "(" << vertex[3].x << ";" << vertex[3].y << ")" << endl;
	ost << endl << "Текущий угол: " << angle << endl;
	color_type temp = get_color();
	ost << endl << "Текущий цвет: " << temp << endl << endl;
	
}


