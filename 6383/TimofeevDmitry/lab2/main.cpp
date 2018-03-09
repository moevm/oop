// Timofeev Dmitry № 17 var 6
// Треугольник, ромб, параллелограмм

#include <iostream>
#include <vector>
#include <cmath>
#include "Triangle.h"
#include "Rhomb.h"


int main() {
    Triangle t("green",Point(0,0),Point(1,0),Point(0,1));
    Rhomb r("yellow",7,5);
    Parallelogram p("blue",M_PI/2,3,2);
    //t.translate(5,7);
    t.scale(10);
    t.rotate(M_PI/2);
    p.translate(5,-9);
    p.rotate(M_PI/3);
    p.scale(10);
    std::cout<<t<<"\n"<<r<<"\n"<<p;
    return 0;
}