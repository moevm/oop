// TEST1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
//#include "lr2.h"
#include <gtest/gtest.h>
#include "RightTriangle.h"
#include "Square.h"
#include "IsoscelesTriangle.h"
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
///*
TEST(Figure_Tests, SameShape)
{ 

RightTriangle testShape(Point (0,0),Point (4,0),Point(0,4));
Square sh1(Point(0,0), Point(4,0), Point(0,4),Point(4,4));
RightTriangle sh2(Point(0,4), Point(4,0), Point(4,4));
	   
	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}

TEST(Figure_Tests, RTriangle_SquareRightTInside)
{
RightTriangle testShape(Point (0,0),Point (4,0),Point(0,4));
Square sh1(Point(0,0), Point(4,0), Point(0,4),Point(4,4));
RightTriangle sh2(Point(0,4), Point(4,0), Point(4,4));
	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}
TEST(Figure_Tests, RTriangle_RTriangle_SquareRightOutsideP)
{
	RightTriangle testShape(Point(0, 0), Point(4, 0), Point(0, 4));
	Square sh1(Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4));
	RightTriangle sh2(Point(0, 4), Point(4, 0), Point(4, 4));
	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}
TEST(Figure_Tests, RTriangle_RTriangle_SquareRightOutsideP)
{
	RightTriangle testShape(Point(0, 0), Point(4, 0), Point(0, 4));
	Square sh1(Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4));
	RightTriangle sh2(Point(0, 4), Point(4, 0), Point(4, 4));

	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}


TEST(Figure_Tests, outside)
{
	RightTriangle testShape(Point(0, 0), Point(4, 0), Point(0, 4));
	Square sh1(Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4));
	RightTriangle sh2(Point(0, 4), Point(4, 0), Point(4, 4));
EXPECT_EQ(false,testShape.similar(sh1, sh2) );
}
//*/
int main(int argc,char* argv[])
{
//	testing::InitGoogleTest(&argc, argv);
  //  RUN_ALL_TESTS();
	
	
	//vector<Point> a;
	//Point l (2,3);
	//l.show();
	//a.push_back(l);
	//a[0].show();
	//vector<Point> b=a;
	//b[0].show();
	//cout << "ENDTST" << endl;
	
	
	
	int size = 4;
	std::vector<Point> array;
	double x;
	double y;
	for (int i = 0; i<size - 1; i++)
	{
		cout << "!" << endl;
		cin >> x;
		cin >> y;
		Point point(x,y);
		array.push_back(point);
		
	}

	//array.size = 3;

	RightTriangle s(array);
	cout << s;
	std::vector<Point> array1;
	for (int i = 0; i<size; i++)
	{
		cout << "!" << endl;
		cin >> x;
		cin >> y;
		Point point(x,y);
		array1.push_back(point);
		//array1.ys.push_back(y);
	}

	//array1.size = 4;
	Square q(array1);
	cout << q;
	//cout<<"S "<<q.area();
	std::vector<Point> array2;
	for (int i = 0; i<size - 1; i++)
	{
		cin >> x;
		cin >> y;
		Point point(x,y);
		array2.push_back(point);
		//array2.ys.push_back(y);
	}



	//array2.size = 3;
	RightTriangle z(array2);
	cout << z;
	std::cout << "BEGIIIIN" << std::endl;
	cout << s;
	cout << q;
	cout << z;
	
	//Square test(Point(0, 0), Point(5, 5), Point(5, 0), Point(0, 5));
	//cout << test;
	//cout << "Similar or not " << s.similar(q, z) << endl;;
	//*/
	system("pause");

    return 0;
}

