#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "../../../src/triangle.h"
#include "../../../src/rectangle.h"

// Тесты прямоугольника без поворота
TEST(RectangleSplitTest, UnturnedRectangle1)
{
    Triangle *t1 = new Triangle();
    Triangle *t2 = new Triangle();

    Triangle res1(Point2d(0, 0), Point2d(0, 1), Point2d(2, 1));
    Triangle res2(Point2d(0, 0), Point2d(2, 0), Point2d(2, 1));

    Rectangle *rect = new Rectangle(Point2d(1, 0), 2, 1);

    Rectangle::split(rect, t1, t2);

    ASSERT_EQ(*t1, res1);
    ASSERT_EQ(*t2, res2);

    delete t1;
    delete t2;
}

TEST(RectangleSplitTest, UnturnedRectangle2)
{
    Triangle *t1 = new Triangle();
    Triangle *t2 = new Triangle();

    Triangle res1(Point2d(1.5, 1.5), Point2d(1.5, 0), Point2d(0, 0));
    Triangle res2(Point2d(0, 0), Point2d(0, 1.5), Point2d(1.5, 0));

    Rectangle *rect = new Rectangle(Point2d(1.5, 1.5), 1.5, 1.5);

    Rectangle::split(rect, t1, t2);

    ASSERT_EQ(*t1, res1);
    ASSERT_EQ(*t2, res2);

    delete t1;
    delete t2;
}

// Тесты прямоугольника, повернутого на угол
TEST(RectangleSplitTest, TurnedRectangle1)
{
    Triangle *t1 = new Triangle();
    Triangle *t2 = new Triangle();

    double c = sqrt(2);

    Triangle res1(Point2d(0, c), Point2d(-c, 0), Point2d(c, 0));
    Triangle res2(Point2d(0, -c), Point2d(-c, 0), Point2d(c, 0));

    Rectangle *rect = new Rectangle(Point2d(1, 1), 2, 2, M_PI / 4);

    Rectangle::split(rect, t1, t2);

    ASSERT_EQ(*t1, res1);
    ASSERT_EQ(*t2, res2);

    delete t1;
    delete t2;
}

TEST(RectangleSplitTest, TurnedRectangle2)
{
    Triangle *t1 = new Triangle();
    Triangle *t2 = new Triangle();

    Triangle res1(Point2d(0, 0), Point2d(-2, 0), Point2d(0, 1));
    Triangle res2(Point2d(-2, 1), Point2d(-2, 0), Point2d(0, 1));

    Rectangle *rect = new Rectangle(Point2d(0, 2), 1, 2, M_PI / 2);

    Rectangle::split(rect, t1, t2);

    ASSERT_EQ(*t1, res1);
    ASSERT_EQ(*t2, res2);

    delete t1;
    delete t2;
}

TEST(RectangleSplitTest, BadRectangles)
{
    // Прямоугольник с отрицательными сторонами
    ASSERT_DEATH( { Rectangle(Point2d(1, 2), -1, -2); }, "");
    // Прямоугольник с нулевыми сторонами
    ASSERT_DEATH( { Rectangle(Point2d(5, -1), 0, 0); }, "");
}
