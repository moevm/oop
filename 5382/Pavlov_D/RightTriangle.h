#pragma once
#include "shape.h"

class RightTriangle : public Triangle
{
public:

	RightTriangle() :Triangle()
	{

		// colour_=0;
		// pointCount_3;
		//  ID_=0;
	}
	RightTriangle(Point array) :Triangle(array) {
		/*
		if (array.size!=3)
		throw std::invalid_argument("Not enought/Too much points");
		pointCount_=3;
		if (!checkSame(array))
		throw std::invalid_argument("Shape have Equal points ");


		// std::vector <double  > side;
		countSides(side,array);
		*/

		double  maxSide = side[0];
		//проверка на свойства прямоугольного треугольника
		//Поиск гипотинузы .Далее проверка Т Пифагора

		if ((side[0] == side[1]) && (side[0] == side[2]) && (side[2] == side[1]))
			throw std::invalid_argument("sides are same");
		for (int i = 1; i<pointCount_; ++i)
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

		/* else {
		if ((side[0]>side[1])&&  (side[0]>side[2])) {
		buffer=sqrt(pow(side[1],2.0)+pow(side[2],2.0));
		if (side[0]!=buffer)
		throw std::invalid_argument ("T.Pishagor wrong");
		}
		if ((side[1]>side[0])&&  (side[1]>side[2])) {
		buffer=sqrt(pow(side[2],2.0)+pow(side[0],2.0));
		if (side[1]!=buffer)
		throw std::invalid_argument("T.Pishagor wrong");
		}
		if ((side[2]>side[1])&&(side[2]>side[0])) {
		buffer=sqrt((pow(side[1],2.0)+pow(side[0],2.0)));
		if (side[2]!=buffer)
		throw std::invalid_argument ("T.Pishagor wrong");
		}

		}
		*/
		colour_ = 0;
		makePoint(array);
		ID_ = setNextID();

	}
	~RightTriangle() {


	}

	void showShape(std::ostream &os) const  override
	{
		os << "I'm Right Triangle" << std::endl;
		for (int i = 0; i<pointCount_; ++i) {
			os << "POINT " << i + 1 << "(" << point_.xs[i] << ";" << point_.ys[i] << ")" << std::endl;
		}

	}

};
