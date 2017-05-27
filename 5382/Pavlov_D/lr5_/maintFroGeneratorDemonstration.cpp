
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
	srand(time(0));
	long int limit = 80;
	long int MAX = 100;
	stepik::vector<stepik::shared_ptr<Shape>> shapesArray=generate_shape_array(MAX,limit);
	stepik::shared_ptr<Point> testP(new Point(0, 0));
	stepik::shared_ptr<Shape> field(new Square({ Point(0,0),Point(40,40),Point(0,40),Point(40,0) }));
	stepik::shared_ptr<Shape> testShape(new RightTriangle({ Point(0,0),Point(0,40),Point(40,0) }));
	stepik::vector<stepik::shared_ptr<Shape>> trueReuslt;
	stepik::vector<stepik::shared_ptr<Shape>> falseResult;
	std::cout << *find_first_shape_inside_point(testShape, field, shapesArray) << std::endl;;
	split_shapes(shapesArray, testP, trueReuslt, falseResult);
	std::cout << "TRUE Result" << std::endl;
	for (size_t q = 0; q < trueReuslt.size(); ++q)
		std::cout << *trueReuslt[q] << std::endl;
	std::cout << "FALSE Result" << std::endl;
	for (size_t q = 0; q < falseResult.size(); ++q)
		std::cout << *falseResult[q] << std::endl;	
	system("pause");
	return 0;
}

