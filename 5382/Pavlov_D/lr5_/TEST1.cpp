
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "alg.h"
#include "generator.h"
using namespace std;

int main(int argc, char* argv[])
{
	long int limit = 60;
	long int MAX = 3;
	stepik::vector<stepik::shared_ptr<Shape>> shapesArray=generate_shape_array(MAX,limit);
	
	stepik::shared_ptr<Point> testP(new Point(20, 20));
	stepik::shared_ptr<Shape> field(new Square({ Point(0,0),Point(40,40),Point(0,40),Point(40,0) }));
	stepik::shared_ptr<Shape> testShape(new RightTriangle({ Point(0,0),Point(0,40),Point(40,0) }));
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
		
	system("pause");

	return 0;
}

