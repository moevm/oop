#include "triangle.h"
#include <math.h>
#include <assert.h>

Triangle::Triangle():Shape(0, RGB(), Point()){
    points.clear();
    sides.clear();
    Point A = {0.0, 2.0};
    Point B = {6.0, 3.0};
    Point C = {12.0, 1.0};
    points.push_back(C);
    points.push_back(B);
    points.push_back(A);
    calculation_sides(A,B,C);

}


Triangle::Triangle(const Point A, const Point B, const Point C, const RGB _colour) : Shape(0, _colour, Point((A.x+B.x+C.x)/3, (A.y+B.y+C.y)/3)){
    points.clear();
    sides.clear();
    points.push_back(C);
    points.push_back(B);
    points.push_back(A);
    calculation_sides(A,B,C);
}

void Triangle::calculation_sides(Point A, Point B, Point C){
    sides.clear();
    double AB = sqrt(pow((A.x - B.x) , 2.0) + pow((A.y - B.y) , 2.0));
    double BC = sqrt(pow((B.x - C.x) , 2.0) + pow((B.y - C.y) , 2.0));
    double CA = sqrt(pow((C.x - A.x) , 2.0) + pow((C.y - A.y) , 2.0));
    sides.push_back(CA);
    sides.push_back(BC);
    sides.push_back(AB);
}



void Triangle::scale(int k){
    Point begin;
    begin.x = point.x;
    begin.y = point.y;
    double X =0, Y = 0;
    for(auto& pnt : points){
        pnt.x *= k;
        X += pnt.x;
       pnt.y *= k;
        Y += pnt.y;
    }
    Point C = Point(points[0].x, points[0].y);
    Point B = Point(points[1].x, points[1].y);
    Point A = Point(points[2].x, points[2].y);
    calculation_sides(A,B,C);
    point.x = X/3;
    point.y = Y/3;
    move(begin);

}


double Triangle::area(){
    double AC = sides[0];
    double BC = sides[1];
    double AB = sides[2];
    double p = (AC + BC + AB)/2;
    double area = sqrt(p*(p-AB)*(p-AC)*(p-BC));
    return area;
}

std::ostream& operator<<(std::ostream& out, Triangle& triangle){
    out << "Triangle" << std::endl;
    out<< "================================="<<std::endl;
    out << (Shape&)triangle;
    out << "Points:"<<std::endl <<"("<< triangle.points[0].x << ", " << triangle.points[0].y << ")" << std::endl;
    out << "(" << triangle.points[1].x << ", " << triangle.points[1].y << ")" << std::endl;
    out << "(" << triangle.points[2].x << ", " << triangle.points[2].y << ")" << std::endl;
    out << "Sides: AC = " << triangle.sides[0] << " BC = " << triangle.sides[1] << " AB = " << triangle.sides[2] << std::endl;
    out << "=========================="<<std::endl;
    return out;
}

Triangle::~Triangle(){
    sides.clear();
    points.clear();

}




