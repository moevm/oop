#include "trapeze.hpp"

Trapeze::Trapeze(Color color, Point V1, Point V2, Point V3, Point V4) : Shape(color), v1(V1), v2(V2), v3(V3), v4(V4) {
    double angle12, angle34;
    angle12 = asin((v2.y - v1.y) / v2.distance(v1));
    if(v2.x - v1.x < eps)
	angle12 = M_PI - angle12;
    angle34 = asin((v4.y - v3.y) / v4.distance(v3));
    if(v4.x - v3.x < eps)
	angle34 = M_PI - angle34;
    if(std::abs(angle12 - angle34) > eps){
	if(std::abs(std::abs(angle12 - angle34) - M_PI) > eps){
	    double angle13, angle24;
	    angle13 = asin((v3.y - v1.y) / v3.distance(v1));
	    if(v3.x - v1.x < eps)
		angle12 = M_PI - angle12;
	    angle24 = asin((v4.y - v2.y) / v4.distance(v2));
	    if(v4.x - v2.x < eps)
		angle34 = M_PI - angle34;
	    if(std::abs(angle13 - angle24) < eps){
		std::swap(v2, v3);
		angle12 = angle13;
	    }
	    else if(std::abs(std::abs(angle13 - angle24) - M_PI) < eps) { 
		std::swap(v2, v3);
		std::swap(v3, v4);
		angle12 = angle13;
	    }
	    else throw std::invalid_argument("Vertexes don't compoze a trapeze");
	}
	else std::swap(v3, v4);
    }
    double angle23 = asin((v3.y - v2.y) / v3.distance(v2));
    if(std::abs(angle23 - angle12) < eps || std::abs(std::abs(angle23 - angle12) - M_PI) < eps)
	throw std::invalid_argument("Vertexes don't compoze a trapeze");
    double k = v2.distance(v1) / v4.distance(v3);
    double r = v3.distance(v2);
    double angle = asin((v2.y - v3.y) / r);
    if(v2.x - v3.x < eps)
	angle = M_PI - angle;
    center.x = v3.x + r / (k + 1) * cos(angle);
    center.y = v3.y + r / (k + 1) * sin(angle);
}

void Trapeze::scale(double scale_ratio){
    double r1, r2, r3, r4;
    double angle1, angle2, angle3, angle4;
    r1 = center.distance(v1);
    angle1 = asin((v1.y - center.y) / r1);
    if(std::abs(v1.x - center.x) < eps)
	angle1 = M_PI - angle1;
    v1.y = center.y + scale_ratio * r1 * sin(angle1);
    v1.x = center.x + scale_ratio * r1 * cos(angle1); 
    r2 = center.distance(v2);
    angle2 = asin((v2.y - center.y) / r2);
    if(std::abs(v2.x - center.x) < eps)
	angle2 = M_PI - angle2;
    v2.y = center.y + scale_ratio * r2 * sin(angle2);
    v2.x = center.x + scale_ratio * r2 * cos(angle2); 
    r3 = center.distance(v3);
    angle3 = asin((v3.y - center.y) / r3);
    if(std::abs(v3.x - center.x) < eps)
	angle3 = M_PI - angle3;
    v3.y = center.y + scale_ratio * r3 * sin(angle3);
    v3.x = center.x + scale_ratio * r3 * cos(angle3); 
    r4 = center.distance(v4);
    angle4 = asin((v4.y - center.y) / r4);
    if(std::abs(v4.x - center.x) < eps)
	angle4 = M_PI - angle4;
    v4.y = center.y + scale_ratio * r4 * sin(angle4);
    v4.x = center.x + scale_ratio * r4 * cos(angle4); 
}

void Trapeze::relocate(Point new_center){
    v1.x += new_center.x - center.x;
    v1.y += new_center.y - center.y;
    v2.x += new_center.x - center.x;
    v2.y += new_center.y - center.y;
    v3.x += new_center.x - center.x;
    v3.y += new_center.y - center.y;
    v4.x += new_center.x - center.x;
    v4.y += new_center.y - center.y;
    center = new_center;
}
void Trapeze::rotate(double angle){
    double r1, r2, r3, r4;
    double angle1, angle2, angle3, angle4;
    r1 = center.distance(v1);
    angle1 = asin((v1.y - center.y) / r1);
    if(std::abs(v1.x - center.x) < eps)
	angle1 = M_PI - angle1;
    angle1 -= angle;
    v1.y = center.y + r1 * sin(angle1);
    v1.x = center.x + r1 * cos(angle1); 
    r2 = center.distance(v2);
    angle2 = asin((v2.y - center.y) / r2);
    if(std::abs(v2.x - center.x) < eps)
	angle2 = M_PI - angle1;
    angle2 -= angle;
    v2.y = center.y + r2 * sin(angle2);
    v2.x = center.x + r2 * cos(angle2); 
    r3 = center.distance(v3);
    angle3 = asin((v3.y - center.y) / r3);
    if(std::abs(v3.x - center.x) < eps)
	angle3 = M_PI - angle3;
    angle3 -= angle;
    v3.y = center.y + r3 * sin(angle3);
    v3.x = center.x + r3 * cos(angle3); 
    r4 = center.distance(v4);
    angle4 = asin((v4.y - center.y) / r4);
    if(std::abs(v4.x - center.x) < eps)
	angle4 = M_PI - angle4;
    angle4 -= angle;
    v4.y = center.y + r4 * sin(angle4);
    v4.x = center.x + r4 * cos(angle4); 

}

std::ostream & Trapeze::print(std::ostream & ostream) const {
    return ostream << "Trapeze id=" << get_id() << std::endl <<  "Color: " << get_color() << std::endl << "Vertexes: " << v1 << v2 << v3 << v4 << std::endl << std::endl;
}
