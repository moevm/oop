#include "Classes.h"
#include "gtest\gtest.h"

int main() {
    //setlocale(LC_ALL,"Russian");
    Point pnt1(1,1);
    Point pnt2(2,2);
    Point pnt3(3,3);
    Point pnt4(4,4);
    Point pnt5(5,5);
    double angle = 90;
    double R = 1;


    TEST(moving, arc) {
        Arc arc (pnt1, pnt2, angle, red);

        arc.move(pnt3)

        EXPECT_EQ(arc.get_id(), 1);
        EXPECT_EQ(arc.get_center(), pnt3);
        EXPECT_EQ(arc.get_angle(), angle);
    }

    TEST(moving, circle) {
        Circle circle (pnt1, R, green);

        circle.move(pnt2)

        EXPECT_EQ(circle.get_radius(), R);
        EXPECT_EQ(circle.get_center(), pnt2);
        EXPECT_EQ(circle.get_id(), 2);
    }

    TEST(moving, ellipse) {
        Ellipse ellipse (pnt1, pnt2, blue);

        ellipse.move(pnt4)

        EXPECT_TRUE(ellipse.get_left_focus()!=pnt1);
        EXPECT_FALSE(ellipse.get_right_focus()==pnt2);
        EXPECT_EQ(ellipse.get_id(), 3);
    }

    TEST(rotating, arc) {
        Arc arc2 (pnt2, pnt3, 90, red);

        arc2.rotate(angle);

        EXPECT_EQ(arc2.get_angle(), angle);
        EXPECT_EQ(arc2.get_id(), 4);
        EXPECT_TRUE(arc2.get_center()!=pnt2);
    }

    TEST(rotating, circle) {
        Circle circle2 (pnt2, R, green);

        circle2.rotate(angle)

        EXPECT_EQ(circle2.get_radius(), R);
        EXPECT_TRUE(circle2.get_center()!=pnt2);
        EXPECT_EQ(circle2.get_id(), 5);
    }

    TEST(rotating, ellipse) {
        Ellipse ellipse2 (pnt2, pnt3, blue);

        ellipse2.rotate(angle)

        EXPECT_TRUE(ellipse2.get_left_focus()!=pnt2);
        EXPECT_FALSE(ellipse2.get_right_focus()==pnt3);
        EXPECT_EQ(ellipse2.get_id(), 6);
    }

    TEST(zooming, arc) {
        Arc arc3 (pnt3, pnt4, 90, red);

        arc3.zoom(2);

        EXPECT_EQ(arc3.get_angle(), angle);
        EXPECT_EQ(arc3.get_id(), 7);
        EXPECT_TRUE(arc3.get_center()==pnt3);
    }

    TEST(zooming, circle) {
        Circle circle3 (pnt3, R, green);

        circle3.zoom(2)

        EXPECT_FALSE(circle3.get_radius()==R);
        EXPECT_TRUE(circle3.get_center()==pnt3);
        EXPECT_EQ(circle3.get_id(), 8);
    }

    TEST(zooming, ellipse) {
        Ellipse ellipse3 (pnt3, pnt4, blue);

        ellipse3.rotate(angle)

        EXPECT_TRUE(ellipse3.get_left_focus()!=pnt3);
        EXPECT_FALSE(ellipse3.get_right_focus()==pnt4);
        EXPECT_EQ(ellipse3.get_id(), 9);
    }
    return 0;
}
