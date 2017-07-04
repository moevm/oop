#include "Classes.h"

int main() {
    setlocale(LC_ALL,"Russian");
    Point pnt1(1,1);
    Point pnt2(2,2);
    Point pnt3(3,3);
    Point pnt4(4,4);
    Point pnt5(5,5);
    double angle = 90;
    double R = 1;

    Arc demo_arc (pnt1, pnt2, angle, red);
    demo_arc.zoom(10);
    std::cout << demo_arc;

    Circle demo_circle (pnt1, R, green);
    demo_circle.move(pnt5);
    std::cout << demo_circle;

    Ellipse demo_ellipse (pnt3, pnt4, blue);
    std::cout << demo_ellipse;

    return 0;
}
