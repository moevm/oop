#include "triangle.h"

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3, const Color& color)
    :Shape(Point((p1.x+p2.x+p3.x)/3, (p1.y+p2.y+p3.y)/3), color)
{
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    a = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    b = sqrt((p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y));
    c = sqrt((p3.x - p1.x)*(p3.x - p1.x) + (p3.y - p1.y)*(p3.y - p1.y));
}

Triangle::Triangle(const Triangle& other)
    :Shape(other.pos, other.color),
     points(other.points),
     a(other.a),
     b(other.b),
     c(other.c)
{
    angle = other.angle;
}

void Triangle::move(const Point& p){
    double x_diff = p.x - pos.x;
    double y_diff = p.y - pos.y;
    pos.x += x_diff;
    pos.y += y_diff;
    for(auto& el : points){
        el.x += x_diff;
        el.y += y_diff;
    }
}

void Triangle::scale(double scale){
    for(auto& el : points){
        el.x *= scale;
        el.y *= scale;
    }
    a = sqrt((points[0].x - points[1].x)*(points[0].x - points[1].x)
            + (points[0].y - points[1].y)*(points[0].y - points[1].y));
    b = sqrt((points[1].x - points[1].x)*(points[1].x - points[2].x)
            + (points[1].y - points[2].y)*(points[1].y - points[2].y));
    c = sqrt((points[2].x - points[0].x)*(points[2].x - points[0].x)
            + (points[2].y - points[0].y)*(points[2].y - points[0].y));
}

void Triangle::turn(double angle){
    this->angle += angle;
    for(auto& el : points){
        el.x *= el.x*cos(angle*M_PI/180) - el.y*sin(angle*M_PI/180);
        el.y *= el.x*sin(angle*M_PI/180) + el.y*cos(angle*M_PI/180);
    }
}

std::vector<double> Triangle::sides(){
    return std::vector<double>{a, b, c};
}

std::ostream& operator<<(std::ostream& os, Triangle& s){
    os << "---Triangle---\n";
    os << (Shape&)s;
    std::vector<double> sides = s.sides();
    os << "Sides: " << sides[0] << " " << sides[1] << " " << sides[2] << '\n';
    os << "--------------\n";
}
