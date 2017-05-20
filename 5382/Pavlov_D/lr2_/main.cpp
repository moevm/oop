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
RightTriangle sh1(Point(0,4), Point(0,0), Point(4,0));
RightTriangle sh2(Point(4,4), Point(4,5), Point(5,4));
	   
	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}

TEST(Figure_Tests, RTriangle_SquareRightTInside)
{
RightTriangle testShape(Point (0,0),Point (4,0),Point(0,4));
Square sh1(Point(0,0), Point(4,0), Point(0,4),Point(4,4));
RightTriangle sh2(Point(0,4), Point(4,0), Point(4,4));
	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}
TEST(Figure_Tests, RTriangle_SquareRightOutsideP)
{
	RightTriangle testShape(Point(0, 0), Point(4, 0), Point(0, 4));
	Square sh1(Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4));
	RightTriangle sh2(Point(-1, 5), Point(4, 0), Point(4, 5));
	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}
TEST(Figure_Tests, RTriangle_RTriangle_SquareRightOutsideP)
{
	RightTriangle testShape(Point(0, 0), Point(4, 0), Point(0, 4));
	Square sh1(Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4));
	IsoscelesTriangle sh2(Point(4, 0), Point(4, 8), Point(4, 4));

	EXPECT_EQ(true,testShape.similar(sh1, sh2) );
}



//*/
int main(int argc,char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
	
	system("pause");

    return 0;
}

