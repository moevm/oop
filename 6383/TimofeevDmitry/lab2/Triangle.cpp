#include "Triangle.h"

Triangle::Triangle(std::string color,const Point& a,const Point& b, const Point& c):Shape(color){
    pts.push_back(a);
    pts.push_back(b);
    pts.push_back(c);
}
void Triangle::applyForAnyPoint(std::function<void(Point&)> const & f) {
    for(Point& p:pts)f(p);
};
std::string Triangle::toString() const  {
    return std::string("Shape = Triangle\n")
           +"id = "+std::to_string(getId())+"\ncolor = "+getColor().def+"\n"+"vertexes:\n"
           +"\t"+std::to_string(pts[0].x)+" "+std::to_string(pts[0].y)+"\n"+
           +"\t"+std::to_string(pts[1].x)+" "+std::to_string(pts[1].y)+"\n"+
           +"\t"+std::to_string(pts[2].x)+" "+std::to_string(pts[2].y)+"\n";

}