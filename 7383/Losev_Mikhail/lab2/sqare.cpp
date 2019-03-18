#include "sqare.h"

Sqare::Sqare()
{
	set_color(COLORLESS);
	ver_num = 4;
	p_vertexes = new Point[ver_num];
	set_center(Point(0, 0));
	set_vertexes(Point(0, 0));
}

Sqare::Sqare(Point cntr, Point v)
{
	set_color(COLORLESS);
	ver_num = 4;		
	p_vertexes = new Point [ver_num];	
	set_center(cntr);
	set_vertexes(v);
}

Sqare::~Sqare()
{ /* std::cout << "Sqare destructor" << std::endl; */ }


std::ostream & Sqare::print(std::ostream & out) const 
{
	out << "\tSqare id: " << get_id() << std::endl;
	return Polygon::print_info(out);
}