#include "polygon.h"

void Polygon::translate2d(const Point2d dp)
{
    for (Point2d p : vertices)
        p.translate2d(dp);
}


void Polygon::rotate(double angle)
{
    for (Point2d p : vertices)
        p.rotate(angle);
}


void Polygon::scale(double scale)
{
    for (Point2d p : vertices)
        p.scale(scale);
}


void Polygon::print(std::ostream& os) const
{
    std::string ColorName[] = { "red", "orange", "yellow", "green", "light_blue", "blue", "purple", "white", "black" };


    os << "Id: " << m_id << std::endl;
    os << "Color: " << ColorName[m_color] << std::endl;

    os << "Area: " << area() << std::endl;
    os << "Perimeter: " << perimeter() << std::endl;

    os << "Vertices: " << std::endl;

    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        os << "\t{ x = " << it->x << "; y = " << it->y << " }" << std::endl;
    }
}
