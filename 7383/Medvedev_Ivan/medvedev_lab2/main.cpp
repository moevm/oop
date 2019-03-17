#include <iostream>
#include "shape.h"
#include "triangle.h"
#include "righttriangle.h"
#include "ellipse.h"

int main(){
       Triangle tri;
       std::cout<<"Standart constructor for triangle"<<tri<<std::endl<<std::endl<<"Moving to (-1,1), scaling, rotate 30"<<std::endl;
       tri.move({-1,1});
       tri.scale(3);
       tri.rotate(30);
       std::cout << tri << std::endl;

       RightTriangle rtri({0, 0}, 4.5, 5.0, RGB());
       std::cout<<"Constructor for right triangle"<<rtri<<std::endl<<"Set green color, rotate 90"<<std::endl;
       rtri.set_colour(RGB(0, 255, 0));
       rtri.rotate(180);
       std::cout << rtri << std::endl;

       Ellipse ell({0,0}, 5, 5, RGB());
       std::cout<<"Constructor for right triangle"<<ell<<std::endl<<"Moving to (2, 3), scaling, set white colour "<<std::endl;
       ell.move({2,3});
       ell.scale(2);
       ell.set_colour(RGB(255,255,255));
       std::cout << ell << std::endl;


}
