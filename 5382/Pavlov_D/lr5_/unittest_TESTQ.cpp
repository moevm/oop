#include <gtest\gtest.h>
#include <generator.h>
#include <alg.h>
TEST(Figure_Tests, SameShape)
{
	
	RightTriangle testShape( { Point(0, 0), Point(4, 0), Point(0, 4) });
	RightTriangle sh1({ Point(0, 4), Point(0, 0), Point(4, 0) });
	RightTriangle sh2({ Point(4, 4), Point(4, 5), Point(5, 4) });

	EXPECT_EQ(false, testShape.similar(sh1, sh2));
}

TEST(Figure_Tests, RTriangle_SquareRightTInside)
{
	
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	RightTriangle sh2({ Point(0, 4), Point(4, 0), Point(4, 4) });
	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Figure_Tests, RTriangle_SquareRightOutsideP)
{
	
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	RightTriangle sh2({ Point(-1, 5), Point(4, 0), Point(4, 5) });
	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Figure_Tests, RTriangle_RTriangle_SquareRightOutsideP)
{
	
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1( {Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	IsoscelesTriangle sh2({ Point(4, 0), Point(4, 8), Point(4, 4) });

	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Vector_Tests, input)
{
	stepik::vector<int> test;
	test.push_back(5);
	test.push_back(777);

	EXPECT_EQ(5, test[0]);
}
TEST(Shared_Test, result)
{
	stepik::shared_ptr<int> test(new int (777));
	EXPECT_EQ(777,*test );
	
}
TEST(alg_Test, FindFirst)
{
	stepik::shared_ptr<Shape> result( new RightTriangle({ Point(0, 0), Point(4, 0), Point(0, 4) }));
	stepik::shared_ptr<Shape> field(new  Square({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) }));
	stepik::vector<stepik::shared_ptr<Shape>> testVector;
	stepik::shared_ptr<Shape> test (new RightTriangle({ Point(4, 4), Point(4, 0), Point(0, 4) }));
	testVector.push_back(stepik::shared_ptr<Shape> (new Square({ Point(5,5),Point(1,1),Point(5,1),Point(1,5) })));
	testVector.push_back(stepik::shared_ptr<Shape>(new RightTriangle({ Point(4, 4), Point(4, 0), Point(0, 4) })));
	EXPECT_EQ(*test,*find_first_shape_inside_point(result, field, testVector) ); 
	
}
TEST(alg_Test, split)
{
	stepik::shared_ptr<Point> testP(new Point(4, 4));
	stepik::vector<stepik::shared_ptr<Shape>> trueReuslt;
	stepik::vector<stepik::shared_ptr<Shape>> falseResult;
	stepik::vector<stepik::shared_ptr<Shape>> testVector;
	testVector.push_back(stepik::shared_ptr<Shape>(new Square({ Point(5,5),Point(1,1),Point(5,1),Point(1,5) })));
	testVector.push_back(stepik::shared_ptr<Shape>(new RightTriangle({ Point(4, 4), Point(4, 0), Point(0, 4) })));
	split_shapes(testVector, testP, trueReuslt, falseResult);
	EXPECT_EQ(true, !trueReuslt.empty()); 
}

//*/
GTEST_API_ int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");

	return 0;
}

