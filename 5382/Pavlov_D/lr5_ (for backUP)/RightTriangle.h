#pragma once
#include "shape.h"

class RightTriangle : public Triangle
{
public:

	RightTriangle() :Triangle()
	{

	}
	

	RightTriangle(std::vector<Point> array) :Triangle(array) {

		double  maxSide = side[0];
		//проверка на свойства прямоугольного треугольника
		//Поиск гипотинузы .Далее проверка Т Пифагора

		if ((side[0] == side[1]) && (side[0] == side[2]) && (side[2] == side[1]))
			throw std::invalid_argument("sides are same");
		for (size_t i = 1; i<pointCount_; ++i)
		{
			maxSide = std::max(maxSide, side[i]);

		}


		if (maxSide != side[0])
		{
			if (maxSide != side[2])
				std::swap(side[0], side[1]);
			else
				std::swap(side[0], side[2]);

		}

		double  hyp = sqrt(pow(side[1], 2.0) + pow(side[2], 2.0));
		if (side[0] != hyp)
			throw std::invalid_argument("T.Pifagor wrong");

		colour_ = 0;
		
		 Point_= array ;
		ID_ = setNextID();

	}
	RightTriangle (Point p1, Point p2, Point p3)
	{
		std::vector<Point> buffer;
		buffer.push_back(p1);
		buffer.push_back(p2);
		buffer.push_back(p3);

		RightTriangle bufferTriangle(buffer);
		*this = bufferTriangle;
	}

	void showShape(std::ostream &os) const  override
	{
		os << "I'm Right Triangle" << std::endl;
		for (size_t i = 0; i<pointCount_; ++i) {
			
			os << "POINT " << i + 1 << "(" << Point_[i].getX() << ";" << Point_[i].getY() << ")" << std::endl;
		}

	}

};
