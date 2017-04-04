#include "gtest/gtest.h"
#include "src/Circle.h"
#include "src/RegularPentangle.h"


using namespace std;

Color white_color(0, 0, 0);
RegularPentangle rp(Point(10, 10), Point(0, 10), white_color);
Circle c(10, Point(10, 10), white_color);
Circle c2(5, Point(10, 10), white_color);
Pentangle p(Point(0, 0), Point(25, 0), Point(25, 15), Point(10, 30), Point(0, 15), white_color);
Point point(5, 5);

// Правильный ятиугольник внутри круга
TEST(figures_test, test1) {
    EXPECT_EQ(true, rp.isPointInside(point));
    EXPECT_EQ(true, c.isUnionOf(c, rp));
}

TEST(figures_test, test1_5) {
    EXPECT_EQ(false, rp.isUnionOf(c, rp));
}


// Круг внутри пятиугольника
TEST(figures_test, test2) {
    EXPECT_EQ(true, p.isPointInside(point));
    EXPECT_EQ(true, p.isUnionOf(p, c));
}

TEST(figures_test, test2_5) {
    EXPECT_EQ(false, c.isUnionOf(p, c));
}

// Круг внутри круга
TEST(figures_test, test3) {
    EXPECT_EQ(true, c.isUnionOf(c, c2));
}

TEST(figures_test, test3_5) {
    EXPECT_EQ(false, c2.isUnionOf(c2, c));
}

// Пятиугольник внутри правильного пятиугольника
TEST(figures_test, test4) {
    EXPECT_EQ(true, p.isUnionOf(rp, p));
}

TEST(figures_test, test4_5) {
    EXPECT_EQ(false, rp.isUnionOf(rp, p));
}
