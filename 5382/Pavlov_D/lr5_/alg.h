#pragma once
#include "RightTriangle.h"
#include "Square.h"
#include "IsoscelesTriangle.h"
#include "SharedPtrStepik.h"
#include "vectorStepik.h"

void  findFirstPointInside(stepik::vector<stepik::shared_ptr<Shape>> &randomShape, Point testPoint)
{
	for (size_t i = 0; i < randomShape.size; ++i)
	{
		if (randomShape[i]->insidePoint(testPoint.getX(),testPoint.getY(),*randomShape[i])) { //TO DO change this function
			std::cout << *randomShape[i] << std::endl;
			return;
		}
	}
	std::cout << "No figure" << std::endl;
}

void SplitResults(stepik::shared_ptr<Shape> testShape, stepik::shared_ptr<Shape> fieldShape, stepik::vector<stepik::shared_ptr<Shape>> &cutShape,
	stepik::vector<stepik::shared_ptr<Shape>> &trueReuslt, stepik::vector<stepik::shared_ptr<Shape>> &falseResult)
{
	for (size_t i = 0; i < cutShape.size; ++i)
	{
		if (testShape->similar(*fieldShape, *cutShape[i]))
			trueReuslt.push_back(cutShape[i]);
		else
			falseResult .push_back(cutShape[i]);
	}
}