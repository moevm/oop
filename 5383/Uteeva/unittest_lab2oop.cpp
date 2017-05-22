// unittest_lab2oop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "Pentagon.h"
#include "RegPentagon.h"
#include "round.h"

TEST(testlab2, defaultTest)
{
	Pentagon p1 = Pentagon(Color(0, 0, 0));
	Pentagon p2 = Pentagon(Color(0, 0, 0));
	bool res = p1.isInsideOfAnother(p2);
	EXPECT_EQ(res, true);
}

TEST(testlab2, RoundInPentagonTrue)
{
	Round r = Round(10, Point(0, 0), Color(0, 0, 0));
	Pentagon p = Pentagon(Point(-15, -15), Point(-30, 10), Point(0, 30), Point(30, 10), Point(15, -15), Color(0, 0, 0));
	bool res = r.isInsideOfAnother(p);
	EXPECT_EQ(res, true);
}


/*int main()
{
    return 0;
}
*/
