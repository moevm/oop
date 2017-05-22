#include <gtest\gtest.h>
#include <TESTQ.h>
/*TEST(testMath, myCubeTest)
{
	EXPECT_EQ(1000, 100+900);
}
*/
TEST(Figure_Tests, SameShape)
{
	std::vector<Point> array1{ Point(0, 0), Point(4, 0), Point(0, 4) };
	std::vector<Point> array2{ Point(0, 4), Point(0, 0), Point(4, 0) };
	std::vector<Point> array3{ Point(4, 4), Point(4, 5), Point(5, 4) };
	RightTriangle testShape(array1);
	RightTriangle sh1(array2);
	RightTriangle sh2(array3);

	EXPECT_EQ(false, testShape.similar(sh1, sh2));
}

TEST(Figure_Tests, RTriangle_SquareRightTInside)
{
	std::vector<Point> array1{ Point(0, 0), Point(4, 0), Point(0, 4) };
	std::vector<Point> array2{ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) };
	std::vector<Point> array3{ Point(0, 4), Point(4, 0), Point(4, 4) };
	RightTriangle testShape(array1);
	Square sh1(array2);
	RightTriangle sh2(array3);
	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Figure_Tests, RTriangle_SquareRightOutsideP)
{
	std::vector<Point> array1{ Point(0, 0), Point(4, 0), Point(0, 4) };
	std::vector<Point> array2{ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) };
	std::vector<Point> array3{ Point(-1, 5), Point(4, 0), Point(4, 5) };
	RightTriangle testShape(array1);
	Square sh1(array2);
	RightTriangle sh2(array3);
	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Figure_Tests, RTriangle_RTriangle_SquareRightOutsideP)
{
	std::vector<Point> array1{ Point(0, 0), Point(4, 0), Point(0, 4) };
	std::vector<Point> array2{ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) };
	std::vector<Point> array3{ Point(4, 0), Point(4, 8), Point(4, 4) };
	RightTriangle testShape(array1);
	Square sh1(array2);
	IsoscelesTriangle sh2(array3);

	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}



//*/
GTEST_API_ int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");

	return 0;
}

