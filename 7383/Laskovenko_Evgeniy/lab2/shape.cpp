#include "shape.h"


Shape::Shape(Point cntr)
{
    id = rand();
    clr = COLORLESS;
    centre.x = cntr.x;
    centre.y = cntr.y;
}

Color Shape::get_color() const
{ return clr; }

void Shape::set_color(Color c)
{ clr = c; }

Shape::~Shape()
{
    id = 0;
    crd.clear();
}

std::ostream& operator<<(std::ostream& out, const Shape& obj)
{
    out << "Shape id: " << obj.id << std::endl;
    out << "Shape color: " << obj.get_color() << std::endl;
    out << "Centre coordinates: (" << obj.centre.x << ", " << obj.centre.y << ")\n";
    out << "Points coorditates: ";
    for(unsigned i=0; i<obj.crd.size(); ++i)
        out << '(' << obj.crd[i].x << ", " << obj.crd[i].y << ") ";
    out << std::endl;

    return out;
}
