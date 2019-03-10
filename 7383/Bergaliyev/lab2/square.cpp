#include "square.hpp"

Square::Square(Color color, Point center, Point v) : Shape(color, center), v(v) {}
void Square::scale(double scale_ratio){
    double r = center.distance(v);
    double angle = asin((v.y - center.y) / r);
    v.y = center.y + scale_ratio * r * sin(angle);
    v.x = center.x + scale_ratio * r * cos(angle);
    
}    
void Square::relocate(Point new_center){
    v.x += new_center.x - center.x;
    v.y += new_center.y - center.y;
    center = new_center;
}

void Square::rotate(double angle){
    double r = center.distance(v);
    angle = -angle;
    angle += asin((v.y - center.y) / r);
    v.y = center.y + r * sin(angle);
    v.x = center.x + r * cos(angle);
}
     
std::ostream & Square::print(std::ostream & ostream) const {
    Point v2, v3, v4;
    double r = center.distance(v);
    double angle = asin((v.y - center.y) / r);
    if(v.x - center.x < eps)
	angle = M_PI - angle;
    angle += M_PI/2;
    v2.y = center.y + r * sin(angle);
    v2.x = center.x + r * cos(angle);
    angle += M_PI/2;
    v3.y = center.y + r * sin(angle);
    v3.x = center.x + r * cos(angle);
    angle += M_PI/2;
    v4.y = center.y + r * sin(angle);
    v4.x = center.x + r * cos(angle);
    return ostream << "Square id=" << get_id() << std::endl <<  "Color: " << get_color() << std::endl << "Vertexes: " << v << v2 << v3 << v4 << std::endl << std::endl;
}
