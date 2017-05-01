#pragma once
#include "shape.h"
class IsoscelesTriangle :public Triangle
{
public:
	IsoscelesTriangle() :Triangle()
	{

		//   colour_=0;
		//pointCount_=3;
		//  ID_=0;
	}
	IsoscelesTriangle(Point array) : Triangle(array) {
		/*
		if (array.size!=3)
		throw std::invalid_argument("Not enought/Too much points");
		pointCount_=3;
		//Проверка на сопадение точек

		if (!checkSame(array))
		throw std::invalid_argument("Shape have Equal points ");

		countSides(side,array);
		*/
		//Проверка на свойства Равнобндренного тр-ка

		if ((side[0] != side[1]) && (side[1] != side[2]) && (side[0] != side[2]))
			throw std::invalid_argument("Not Isoscellence");

		colour_ = 0;
		makePoint(array);

		ID_ = setNextID();
	}
	~IsoscelesTriangle() {


	}

	void showShape(std::ostream &os) const override
	{
		os << "I'm IsoscelesTriangle" << std::endl;
		for (int i = 0; i<pointCount_; ++i) {
			os << "POINT " << i + 1 << "(" << point_.xs[i] << ";" << point_.ys[i] << ")" << std::endl;
		}
	}


};