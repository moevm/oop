#include <iostream>

#include "shapes.hpp"

int main(void)
{
    //Tests for circle
    Circle circ(0,0, -123);
    circ.setAngle(11);
    circ.zoom(28);
    std::cout << circ;

    //Tests for Polygon
    Polygon huge(0, 0, true, 38, 20 );
    huge.setAngle( 188888 );
    std::cout << huge;
    Polygon random( 0,0, false, 0, 0 );
    random.makeSimple( 1, 2, 0,0 );
    std::cout << random;

    return 0;
}
