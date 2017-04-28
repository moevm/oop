//
//  Ellipse.cpp
//  WORKPLEASE
//
//  Created by user on 30.03.17.
//  Copyright © 2017 user. All rights reserved.
//

#include "ellipse.h"
#include "math.h"

Ellipse::Ellipse(const Point &center, double a, double b, double fi) :
    Shape(fi), center(center), a(a), b(b)
{
    if(a < 0 || b < 0)
    {
        throw std::invalid_argument("Negative axis are not allowed");
    }
}

void Ellipse::move_to(const Point &p)
{
    center = p;
}

void Ellipse::scale(double scale)
{
    a *= scale;
    b *= scale;
}
void Ellipse :: rotate (double angle)
{
    this->angle = angle;
}

void Ellipse::print(std::ostream& os) const
{
    os << "Ellipse: "<<"a = "<<a<<", b = "<<b<<std::endl;
    os << "Center: " << center.X << "; " << center.Y << std::endl;
    os << "Color: "<<color.r<<" "<<color.g<<" "<<color.b<< std::endl;
    os << "id: "<< id<<std::endl;
}

std::vector<Point> Ellipse::getVertices() const
{
    std::vector<Point> v;
    v.reserve(4);
    v.push_back(Point(center.X - a, center.Y));
    v.push_back(Point(center.X + a, center.Y));
    v.push_back(Point(center.X, center.Y - b));
    v.push_back(Point(center.X, center.Y + b));
    return v;
}
