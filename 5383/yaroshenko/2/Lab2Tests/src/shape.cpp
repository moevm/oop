#include "shape.h"

size_t Shape::count = 0;

Shape::Shape()
{
    m_id = count++;
    m_color = CL_WHITE;
}


void Shape::setColor(Color color)
{
    m_color = color;
}


size_t Shape::getColor() const
{
    return m_color;
}


size_t Shape::getId() const
{
    return m_id;
}

std::ostream& operator<< (std::ostream& os, const Shape& p)
{
    p.print(os);
    return os;
}
