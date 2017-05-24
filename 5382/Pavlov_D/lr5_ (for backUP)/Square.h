#pragma once
#include "shape.h"
class Square :public Shape
{
public:
	Square() :Shape()
	{
	
		pointCount_ = 4;
		
	}
	

	Square(std::vector<Point> array) :Shape(array) {


		pointCount_ = 4;
		
		if (array.size() != pointCount_)
			throw std::invalid_argument("Not enought/Too much points ");
		countSides(side, array);
		
		for (size_t i = 0; i<pointCount_; i++) {
			
			if (side[0] != side[i])
				throw std::invalid_argument("Sides not equal ");
		}

		colour_ = 0;
		 Point_=array;

		ID_ = setNextID();
	}
	
	~Square() {
	
	}
	Square(Point p1, Point p2, Point p3, Point p4)
	{
		std::vector<Point> buffer;
		buffer.push_back(p1);
		buffer.push_back(p2);
		buffer.push_back(p3);
		buffer.push_back(p4);
		Square bufferSquare(buffer);
		*this = bufferSquare;
		


	}

	void showShape(std::ostream &os) const override
	{
		os << "I'm Square" << std::endl;
		for (size_t i = 0; i<pointCount_; ++i) {
			
			os << "POINT " << i + 1 << "(" << Point_[i].getX() << ";" << Point_[i].getY() << ")" << std::endl;
		}
	}
	double  area() const override
	{
		return side[0] * side[0];
	}
	
	virtual void countSides(std::vector<double  > &side, std::vector<Point> array) override
	{
		side.push_back(sqrt(pow(array[0].getX() - array[1].getX(), 2.0) + pow(array[0].getY() - array[1].getY(), 2.0)));//
		side.push_back(sqrt(pow(array[0].getX() - array[2].getX(), 2.0) + pow(array[0].getY() - array[2].getY(), 2.0)));//
		side.push_back(sqrt(pow(array[0].getX() - array[3].getX(), 2.0) + pow(array[0].getY() - array[3].getY(), 2.0)));//
		side.push_back(sqrt(pow(array[2].getX() - array[3].getX(), 2.0) + pow(array[2].getY() - array[3].getY(), 2.0)));//
		side.push_back(sqrt(pow(array[1].getX() - array[3].getX(), 2.0) + pow(array[1].getY() - array[3].getY(), 2.0)));//
		side.push_back(sqrt(pow(array[1].getX() - array[2].getX(), 2.0) + pow(array[1].getY() - array[2].getY(), 2.0)));//
		double  maxSide = side[0];
		int count = 2;
		while (count != 0) {
			for (size_t i = 0; i<array.size(); i++) {
				maxSide = std::max(maxSide, side[i]);
			}

			for (size_t i = 0; i<array.size(); i++) {
				if (maxSide == side[i])
					std::swap(side[i], side[side.size() - 1]);

			}
			side.pop_back();
			count--;
		}


	}

};