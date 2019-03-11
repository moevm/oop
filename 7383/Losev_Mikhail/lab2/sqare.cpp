
#include "sqare.h"

Sqare::Sqare()
{	}

Sqare::Sqare(Point cntr, Point crnr)
{
	set_color(COLORLESS);
	centre = cntr;
	vertex = crnr;

}

void Sqare::rotate(Point cntr, double ang)
{
	centre.rotate(cntr, ang);
	vertex.rotate(cntr, ang);
}
void Sqare::move(Point p)
{
	vertex = (vertex - centre) + p;
	centre = p;
}
void  Sqare::scale(double coef)
{
	//vertex = centre + (vertex - centre) * coef; // не смог перегрузить умножение (???)
	vertex = Point(centre.get_x() + (vertex.get_x() - centre.get_x()) * coef, centre.get_y() + (vertex.get_y() - centre.get_y()) * coef);
}

Sqare::~Sqare()
{	}

std::ostream& operator<<(std::ostream& out, const Sqare& obj)
{
	out << "\tSqare color: " << obj.get_color() << std::endl;
	out << "\tCentre coorditates: (" << obj.centre.get_x() << ", " << obj.centre.get_y() << ")" << std::endl;
	out << "\tVertex coorditates: (" << obj.vertex.get_x() << ", " << obj.vertex.get_y() << ")" << std::endl;
	out << "\tId: " << obj.get_id() << std::endl;

	return out;
}