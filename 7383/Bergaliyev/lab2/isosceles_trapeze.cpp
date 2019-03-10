#include "isosceles_trapeze.hpp"

Isosceles_Trapeze::Isosceles_Trapeze(Color color, Point center, Point v1, Point v2) : Shape(color, center), v1(v1), v2(v2) {
    double r1, r2;
    r1 = center.distance(v1);
    r2 = center.distance(v2);
    double angle1, angle2;
    angle1 = asin((center.y - v1.y) / r1);
    if(center.x - v1.x < eps)
	angle1 = M_PI - angle1;
    angle2 = asin((center.y - v2.y) / r2);
    if(center.x - v2.x < eps)
	angle2 = M_PI - angle2;
    if(std::abs(std::abs(angle1 - angle2) - M_PI) < eps
        || std::abs(angle1 - angle2) < eps)
	throw std::invalid_argument("Vertexes and center mustn't lay on same line");
}

void Isosceles_Trapeze::scale(double scale_ratio){
    double r1, r2;
    r1 = center.distance(v1);
    r2 = center.distance(v2);
    double angle1, angle2;
    angle1 = asin((center.y - v1.y) / r1);
    if(center.x - v1.x < eps)
	angle1 = M_PI - angle1;
    v1.x = center.x + scale_ratio * r1 * cos(angle1);
    v1.y = center.y + scale_ratio * r1 * sin(angle1);
    angle2 = asin((center.y - v2.y) / r2);
    if(center.x - v2.x < eps)
	angle2 = M_PI - angle2;
    v2.x = center.x + scale_ratio * r2 * cos(angle2);
    v2.y = center.y + scale_ratio * r2 * sin(angle2);
}

void Isosceles_Trapeze::rotate(double angle){
    double r1, r2;
    r1 = center.distance(v1);
    r2 = center.distance(v2);
    double angle1, angle2;
    angle1 = asin((center.y - v1.y) / r1);
    if(center.x - v1.x < eps)
	angle1 = M_PI - angle1;
    angle1 -= angle;
    v1.x = center.x + r1 * cos(angle1);
    v1.y = center.y + r1 * sin(angle1);
    angle2 = asin((center.y - v2.y) / r2);
    if(center.x - v2.x < eps)
	angle2 = M_PI - angle2;
    angle2 -= angle;
    v2.x = center.x + r2 * cos(angle2);
    v2.y = center.y + r2 * sin(angle2);
}

void Isosceles_Trapeze::relocate(Point new_center){
    v1.x += new_center.x - center.x;
    v1.y += new_center.y - center.y;
    v2.x += new_center.x - center.x;
    v2.y += new_center.y - center.y;
    center = new_center;
}

std::ostream & Isosceles_Trapeze::print(std::ostream & ostream) const{
    double r1, r2;
    r1 = center.distance(v1);
    r2 = center.distance(v2);
    double angle1, angle2;
    angle1 = asin((center.y - v1.y) / r1);
    if(center.x - v1.x < eps)
	angle1 = M_PI - angle1;
    angle2 = asin((center.y - v2.y) / r2);
    if(center.x - v2.x < eps)
	angle2 = M_PI - angle2;
    Point v3, v4;
    v3.x = center.x + r2 * cos(angle1);
    v3.y = center.y + r2 * sin(angle1);
    v4.x = center.x + r1 * cos(angle2);
    v4.y = center.y + r1 * sin(angle2);
    return ostream << "Isosceles Trapeze id=" << get_id() << std::endl <<  "Color: " << get_color() << std::endl << "Vertexes: " << v1 << v2 << v3 << v4 << std::endl << std::endl;
}
