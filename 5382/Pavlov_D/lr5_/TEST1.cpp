// TEST1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

#include <cmath>
#include <vector>
#include <algorithm>

#include "alg.h"
#include "generator.h"
using namespace std;
const long int MAX = 100;
int main(int argc,char* argv[])
{ 
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	RightTriangle sh2({ Point(0, 4), Point(4, 0), Point(4, 4) });
	std::cout << testShape.similar(sh1, sh2);
	/*
	stepik::vector<stepik::shared_ptr<Shape>> shapesArray;
	long int limit=70;
	for (int count = 0; count < MAX; ++count)
	{
		size_t switch_on = rand() %3 +1;
		switch (switch_on)
		{
		case 1:
		{
			shapesArray.push_back(generat_RightTriangle(limit));//need fix*
			break;
		}
		case 2:
		{
			shapesArray.push_back(generat_RightTriangle(limit));//need fix*
			break;
		}
		case 3:
		{
			shapesArray.push_back(generate_IsoscelesTriangle(limit));//need fix*
			break;
		}
		default:
			break;
		}
	}
	//! 
	stepik::shared_ptr<Point> testP (&Point(20,20));
	stepik::shared_ptr<Shape> field (&Square({Point(0,0),Point(40,40),Point(0,40),Point(40,0)}));
	stepik::shared_ptr<Shape> testShape(&RightTriangle({ Point(0,0),Point(0,40),Point(40,0) }));
	stepik::vector<stepik::shared_ptr<Shape>> trueReuslt;
	stepik::vector<stepik::shared_ptr<Shape>> falseResult;
	find_first_shape_inside_point(testShape, field, shapesArray);
	split_shapes(shapesArray, testP, trueReuslt, falseResult);
	std::cout << "TRUE" << std::endl;
	for (size_t q = 0; q < trueReuslt.size(); ++q)
		std::cout << *trueReuslt[q] << std::endl;
	std::cout << "FALSE" << std::endl;
	for (size_t q = 0; q < trueReuslt.size(); ++q)
		std::cout << *falseResult[q] << std::endl;
		*/
	system("pause");

    return 0;
}

