#include "gtest\gtest.h"
#include "lab5.h"

HDC _hdc = NULL;

stepik::vector< stepik::shared_ptr<shape> > kappa1 =
{
	stepik::shared_ptr<shape>(new circle(50, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0)))),
	stepik::shared_ptr<shape>(new ellipse(100, 200, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new arc(40, 0, 270, paint_area_info(500, 500, 1250, 250, _hdc, rgb_color(0, 0, 255))))
};

stepik::vector< stepik::shared_ptr<shape> > kappa2 =
{
	stepik::shared_ptr<shape>(new arc(40, 0, 270, paint_area_info(500, 500, 1250, 250, _hdc, rgb_color(0, 0, 255)))),
	stepik::shared_ptr<shape>(new ellipse(100, 200, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new circle(50, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0))))
};

stepik::vector< stepik::shared_ptr<shape> > kappa3 =
{
	stepik::shared_ptr<shape>(new ellipse(100, 220, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new ellipse(120, 230, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0)))),
	stepik::shared_ptr<shape>(new ellipse(130, 240, paint_area_info(500, 500, 750, 250, _hdc, rgb_color(0, 255, 0))))
};

stepik::vector< stepik::shared_ptr<shape> > kappa2 =
{
	stepik::shared_ptr<shape>(new circle(50, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0)))),
	stepik::shared_ptr<shape>(new circle(100, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0)))),
	stepik::shared_ptr<shape>(new circle(150, paint_area_info(500, 500, 250, 250, _hdc, rgb_color(255, 0, 0))))
};

TEST(lab5_test, my_func1){
	EXPECT_EQ(same_search(kappa1, kappa2), 1);
	EXPECT_EQ(same_search(kappa3, kappa4), INT_MIN);
}

TEST(lab5_test, my_func2){
	stepik::vector< stepik::shared_ptr<shape> > res = intersection(kappa1, kappa2);
	EXPECT_EQ(res.size(), 1);
	EXPECT_EQ(res[0]->shape_type(), "ellipse");
}