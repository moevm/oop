#include "polygon.h"

Point2d Polygon::getCenter() const
{
    Point2d center;

    for (Point2d p : vertices)
    {
        center.x += p.x;
        center.y += p.y;
    }

    center.x /= vertices.size();
    center.y /= vertices.size();

    return center;
}


void Polygon::translate2d(const Point2d &dp)
{
    for (Point2d p : vertices)
        p.translate2d(dp);
}


void Polygon::rotate(double angle)
{
    Point2d center = getCenter();

    // переносим в начало координат
    translate2d(-center);

    // поворачиваем
    for (Point2d p : vertices)
        p.rotate(angle);

    // возвращаем назад
    translate2d(center);
}


void Polygon::scale(double scale)
{
    Point2d center = getCenter();

    // переносим в начало координат
    translate2d(-center);

    // масштабируем
    for (Point2d p : vertices)
        p.scale(scale);

    // возвращаем
    translate2d(center);
}


void Polygon::print(std::ostream& os) const
{
    os << "Id: " << m_id << std::endl;
    os << "Color: { r=" << m_color.r << ", g=" << m_color.g << ", b=" << m_color.b << " }" << std::endl;

    os << "Area: " << area() << std::endl;
    os << "Perimeter: " << perimeter() << std::endl;

    os << "Vertices: " << std::endl;

    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        os << "\t{ x = " << it->x << "; y = " << it->y << " }" << std::endl;
    }
}
