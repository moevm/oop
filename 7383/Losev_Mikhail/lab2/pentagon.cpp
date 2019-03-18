#include "pentagon.h"

Pentagon::Pentagon()
{
	set_color(COLORLESS);
	ver_num = 5;					//there are 5 vertexes in pentagon
	p_vertexes = new Point[ver_num]; 
	set_center(Point(0, 0));
	set_vertexes(Point(0, 0));
}

Pentagon::Pentagon(Point cntr, Point v)
{
	set_color(COLORLESS);
	ver_num = 5;		
	p_vertexes = new Point [ver_num];	
	set_center(cntr);
	set_vertexes(v);
}

Pentagon::~Pentagon()
{ /* std::cout << "Pentagon destructor" << std::endl; */ }

std::ostream & Pentagon::print(std::ostream & out) const 
{
	out << "\tPentagon id: " << get_id() << std::endl;
	return Polygon::print_info(out);
}