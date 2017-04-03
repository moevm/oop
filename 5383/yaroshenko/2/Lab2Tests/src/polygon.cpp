#include "polygon.h"

void Polygon::translate2d(const Point2d dp)
{
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        it->x += dp.x;
        it->y += dp.y;
    }
}


void Polygon::rotate(double angle)
{
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        double x = it->x;
        double y = it->y;

        it->x = x * cos(angle) - y * sin(angle);
        it->y = x * sin(angle) + y * cos(angle);
    }
}


void Polygon::scale(double scale)
{
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        it->x *= scale;
        it->y *= scale;
    }
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
