#include "polygon.h"

Polygon::Polygon() : ver_num(0), p_vertexes(nullptr)
{	}

int Polygon::get_ver_num() const
{ return ver_num; }

void Polygon::set_ver_num(int n)
{ ver_num = n; }

void Polygon::set_vertexes(Point v)
{ // for a regular polygon, set vertexes evenly
	for (int i = 0; i < ver_num; i++){
		p_vertexes[i] = v;
		v.rotate(centre, 2 * M_PI / ver_num);
	}
}

void Polygon::set_center(Point p)
{ centre = p; }

Point Polygon::get_center() const
{ return centre; }

void Polygon::rotate(Point cntr, double ang)
{
	centre.rotate(cntr, ang);
	for (int i = 0; i < ver_num; i++)
		p_vertexes[i].rotate(cntr, ang);
}

void Polygon::scale(double coef)
{
	for (int i = 0; i < ver_num; i++)
		p_vertexes[i] = Point(centre.get_x() + (p_vertexes[i].get_x() - centre.get_x()) * coef, centre.get_y() + (p_vertexes[i].get_y() - centre.get_y()) * coef);
}

void Polygon::move(Point p)
{
	for (int i = 0; i < ver_num; i++)
		p_vertexes[i] = (p_vertexes[i] - centre) + p;
	centre = p;
}

std::ostream & Polygon::print_info(std::ostream & out) const 
{
	out << "\tColor: " << get_color() << std::endl;
	
	out << "\tCentre coorditates: (" << centre.get_x() << "; " << centre.get_y() << ")" << std::endl;
	out << "\tVertexeses coorditates: ";
	for (int i = 0; i < ver_num; i++)
		out << " (" << p_vertexes[i].get_x() << "; " << p_vertexes[i].get_y() << ") ";
	out << std::endl;
	return out;
}

std::ostream & Polygon::print(std::ostream & out) const 
{
	out << "\t" << ver_num << "-gon id: " << get_id() << std::endl;
	return Polygon::print_info(out);
}

Polygon::~Polygon()
{ if (p_vertexes) delete [] p_vertexes; }