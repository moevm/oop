#pragma once
#include "shape.h"
class IsoscelesTriangle :public Triangle
{
public:
	IsoscelesTriangle() :Triangle()
	{
	}
	
	IsoscelesTriangle(std::vector<Point> array) : Triangle(array) {
		if ((side[0] != side[1]) && (side[1] != side[2]) && (side[0] != side[2]))
			throw std::invalid_argument("Not Isoscellence");

		colour_ = 0;
		//makePoint(array);
		Point_=array ;
		ID_ = setNextID();
	}
	~IsoscelesTriangle() {


	}
	IsoscelesTriangle (Point p1, Point p2, Point p3)
	{
		std::vector<Point> buffer;
		buffer.push_back(p1);
		buffer.push_back(p2);
		buffer.push_back(p3);

	IsoscelesTriangle bufferTriangle(buffer);
		*this = bufferTriangle;
	}


	void showShape(std::ostream &os) const override
	{
		os << "I'm IsoscelesTriangle" << std::endl;
		for (size_t i = 0; i<pointCount_; ++i) {
			
			os << "POINT " << i + 1 << "(" << Point_[i].getX() << ";" << Point_[i].getY() << ")" << std::endl;
		}
	}


};