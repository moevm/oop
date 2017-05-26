#pragma once
#include "RightTriangle.h"
#include "Square.h"
#include "IsoscelesTriangle.h"
#include "SharedPtrStepik.h"
#include "vectorStepik.h"

void  find_first_shape_inside_point(const stepik::shared_ptr<Shape> &testShape, 
	const stepik::shared_ptr<Shape> &fieldShape, const stepik::vector<stepik::shared_ptr<Shape>> &cutShape)//(stepik::vector<stepik::shared_ptr<Shape>> &randomShape, Point testPoint)
{
	for (size_t i = 0; i < cutShape.size(); ++i)
	{
		if (testShape->similar(*fieldShape,*cutShape[i])) { //TO DO change this function
			std::cout << *cutShape[i] << std::endl;
			return;
		}
	}
	std::cout << "No figure" << std::endl;
}

void split_shapes (const stepik::vector<stepik::shared_ptr<Shape>> &randomShape,const  Point &testPoint,
	 stepik::vector<stepik::shared_ptr<Shape>> &trueReuslt, stepik::vector<stepik::shared_ptr<Shape>> &falseResult) 
{
	for (size_t i = 0; i < randomShape.size(); ++i)
	{
		
		if(1) //if (randomShape.insidePoint(Point testPoint)TO_DO change inide Point.
			trueReuslt.push_back(randomShape[i]);
		else
			falseResult .push_back(randomShape[i]);
	}
}