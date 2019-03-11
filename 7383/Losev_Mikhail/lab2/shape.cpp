#include "shape.h"

unsigned int Shape::count = 1; // нельзя в теле класса (???)

Shape::Shape() : id(count), clr(COLORLESS)
{ count++; }

Shape::Shape(color clr) : id(count), clr(clr)
{ count++; }

Shape::Shape(Point centre) : id(count), clr(COLORLESS), centre(centre)
{ count++; }

Shape::Shape(Point centre, color clr) : id(count), clr(clr), centre(centre)
{ count++; }


color Shape::get_color() const
{ return clr; }

void Shape::set_color(color c)
{ clr = c; }

int Shape::get_id() const
{ return id; }

Shape::~Shape()
{	}

std::ostream& operator<<(std::ostream& out, const Shape& obj) 
{
	out << "Shape color: " << obj.get_color() << std::endl;
	out << "Centre coordinates: (" << obj.centre.get_x() << ", " << obj.centre.get_y() << ")" << std::endl;;
	

	return out;
}