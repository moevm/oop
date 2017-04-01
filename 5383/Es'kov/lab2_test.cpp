#include "gtest\gtest.h"
#include "circle.h"
#include "ellipse.h"
#include "arc.h"

HDC hdc = NULL;

TEST(circle_test, constructor){
	circle c(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	EXPECT_DOUBLE_EQ(c.get_radius(), 50);
	c.draw(5, 5);
	EXPECT_DOUBLE_EQ(c.getX(), 5);
	EXPECT_DOUBLE_EQ(c.getY(), 5);
}

TEST(circle_test, perimeter){
	circle c(70, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	EXPECT_DOUBLE_EQ(c.perimetr(), 439.81);
}

TEST(ellipse_test, constructor){
	ellipse e(100, 200, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));
	EXPECT_DOUBLE_EQ(e.get_small_axle(), 100);
	EXPECT_DOUBLE_EQ(e.get_big_axle(), 200);
	e.draw(7, 7);
	EXPECT_DOUBLE_EQ(e.getX(), 7);
	EXPECT_DOUBLE_EQ(e.getY(), 7);
}

TEST(ellipse_test, perimeter){
	ellipse e(75, 125, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	EXPECT_DOUBLE_EQ(e.perimetr(), 628.3);
}

TEST(arc_test, constructor){
	arc a(40, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
	EXPECT_DOUBLE_EQ(a.get_radius(), 40);
	EXPECT_DOUBLE_EQ(a.get_start_angle(), -90);
	EXPECT_DOUBLE_EQ(a.get_stop_angle(), 180);
	a.draw(-5, 0);
	EXPECT_DOUBLE_EQ(a.getX(), -5);
	EXPECT_DOUBLE_EQ(a.getY(), 0);
}

TEST(arc_test, perimeter){
	arc a(79, 30, 180, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	EXPECT_DOUBLE_EQ(a.perimetr(), 206.81541666666666);
}

TEST(shapes_test, perimeter){
	circle c(70, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	ellipse e(75, 125, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	arc a(79, 30, 180, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	EXPECT_DOUBLE_EQ(shape::comparePerimeter(c, e), -1);
	EXPECT_DOUBLE_EQ(shape::comparePerimeter(c, a), 1);
	EXPECT_DOUBLE_EQ(shape::comparePerimeter(e, a), 1);
}