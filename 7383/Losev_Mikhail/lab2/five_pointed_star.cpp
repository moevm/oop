
#include "five_pointed_star.h"

FivePointedStar::FivePointedStar()
{
	set_color(COLORLESS);
	set_center(Point(0, 0));
	ver_num = 5; 
	inner_ver_num = 5;				
	p_vertexes = new Point[ver_num]; 			// extern vertexex
	p_inner_vertexes = new Point[inner_ver_num]; 	// inner vertexes
	set_vertexes(Point(0, 0));
	set_inner_vertexes(Point(0, 0));
}

FivePointedStar::FivePointedStar(Point cntr, Point v)
{
	set_color(COLORLESS);
	set_center(cntr);
	ver_num = 5; 
	inner_ver_num = 5;					
	p_vertexes = new Point [ver_num];	
	p_inner_vertexes = new Point[inner_ver_num]; 
	set_vertexes(v);
	set_inner_vertexes(v);
}

void FivePointedStar::set_inner_vertexes(Point iv)
{
	iv.rotate(centre, M_PI / 5); 		// 36 / 360 * 2 * M_PI = M_PI / 5
	iv.set_x(iv.get_x() * sin(M_PI / 10) / cos(M_PI / 5));
	iv.set_y(iv.get_y() * sin(M_PI / 10) / cos(M_PI / 5));
	
	for (int i = 0; i < inner_ver_num; i++){
		p_inner_vertexes[i] = iv;
		iv.rotate(centre, 2 * M_PI / inner_ver_num);
	}
}

void FivePointedStar::rotate(Point cntr, double ang)
{
	for (int i = 0; i < inner_ver_num; i++)		// rotate inner vertexes
		p_inner_vertexes[i].rotate(cntr, ang);
	Polygon::rotate(cntr, ang);					// rotate extern vertexes
}

void FivePointedStar::move(Point p)
{
	for (int i = 0; i < inner_ver_num; i++)
		p_inner_vertexes[i] = (p_inner_vertexes[i] - centre) + p;
	Polygon::move(p);
}
void  FivePointedStar::scale(double coef)
{
	Polygon::scale(coef);
	for (int i = 0; i < inner_ver_num; i++)
		p_inner_vertexes[i] = Point(centre.get_x() + (p_inner_vertexes[i].get_x() - centre.get_x()) * coef, centre.get_y() + (p_inner_vertexes[i].get_y() - centre.get_y()) * coef);
}

std::ostream& FivePointedStar::print(std::ostream& out) const
{
	out << "\tFivePointedStar id: " << get_id() << std::endl;
	Polygon::print_info(out);

	out << "\tInner vertexeses coorditates: ";
	for (int i = 0; i < inner_ver_num; i++)
		out << " (" << p_inner_vertexes[i].get_x() << "; " << p_inner_vertexes[i].get_y() << ")";
	std::cout << std::endl;

	return out;
}

FivePointedStar::~FivePointedStar()
{ /* std::cout << "FivePointedStar destructor" << std::endl; */ }

