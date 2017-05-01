#pragma once
#include "shape.h"
class Square :public Shape
{
public:
	Square() :Shape()
	{

		//colour_=0;
		pointCount_ = 4;
		// ID_=0;
	}
	Square(Point array) :Shape(array) {


		pointCount_ = 4;

		if (array.size != pointCount_)
			throw std::invalid_argument("Not enought/Too much points ");
		//std::vector<double  > side;
		countSides(side, array);
		for (int i = 0; i<pointCount_; i++) {
			if (side[0] != side[i])
				throw std::invalid_argument("Sides not equal ");
		}

		colour_ = 0;

		makePoint(array);
		area_ = area();

		ID_ = setNextID();
	}
	~Square() {

	}

	void showShape(std::ostream &os) const override
	{
		os << "I'm Square" << std::endl;
		for (int i = 0; i<pointCount_; ++i) {
			os << "POINT " << i + 1 << "(" << point_.xs[i] << ";" << point_.ys[i] << ")" << std::endl;
		}
	}
	double  area() override
	{
		return side[0] * side[0];
	}
	virtual void countSides(std::vector<double  > &side, Point array) override
	{
		side.push_back(sqrt(pow(array.xs[0] - array.xs[1], 2.0) + pow(array.ys[0] - array.ys[1], 2.0)));//
		side.push_back(sqrt(pow(array.xs[0] - array.xs[2], 2.0) + pow(array.ys[0] - array.ys[2], 2.0)));//
		side.push_back(sqrt(pow(array.xs[0] - array.xs[3], 2.0) + pow(array.ys[0] - array.ys[3], 2.0)));//
		side.push_back(sqrt(pow(array.xs[2] - array.xs[3], 2.0) + pow(array.ys[2] - array.ys[3], 2.0)));//
		side.push_back(sqrt(pow(array.xs[1] - array.xs[3], 2.0) + pow(array.ys[1] - array.ys[3], 2.0)));//
		side.push_back(sqrt(pow(array.xs[1] - array.xs[2], 2.0) + pow(array.ys[1] - array.ys[2], 2.0)));//
		double  maxSide = side[0];
		// std::for_each(side.begin(),side.end(),[](double  &n) {maxSide=max(n,maxSide)});
		int count = 2;
		while (count != 0) {
			for (auto i = 0; i<array.size; i++) {
				maxSide = std::max(maxSide, side[i]);
			}

			for (auto i = 0; i<array.size; i++) {
				if (maxSide == side[i])
					std::swap(side[i], side[side.size() - 1]);
				//  side[i].swap(side[3]) ;
			}
			side.pop_back();
			count--;
		}


	}


};