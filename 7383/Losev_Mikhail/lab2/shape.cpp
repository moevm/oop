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
{ /* std::cout << "Shape destructor" << std::endl; */ }

std::ostream& operator<<(std::ostream& out, const Shape & obj) 
{ return obj.print(out); }
