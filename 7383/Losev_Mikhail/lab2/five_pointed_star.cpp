
#include "five_pointed_star.h"

FivePointedStar::FivePointedStar()
{	}

FivePointedStar::FivePointedStar(Point cntr, Point crnr)
{
	set_color(COLORLESS);
	centre = cntr;
	vertex = crnr;

}

void FivePointedStar::rotate(Point cntr, double ang)
{
	centre.rotate(cntr, ang);
	vertex.rotate(cntr, ang);
}
void FivePointedStar::move(Point p)
{
	vertex = (vertex - centre) + p;
	centre = p;
}
void  FivePointedStar::scale(double coef)
{
	//vertex = centre + (vertex - centre) * coef;
	vertex = Point(centre.get_x() + (vertex.get_x() - centre.get_x()) * coef, centre.get_y() + (vertex.get_y() - centre.get_y()) * coef);
}

FivePointedStar::~FivePointedStar()
{	}

std::ostream& operator<<(std::ostream& out, const FivePointedStar& obj)
{
	out << "\tFivePointedStar color: " << obj.get_color() << std::endl;
	out << "\tCentre coorditates: (" << obj.centre.get_x() << ", " << obj.centre.get_y() << ")" << std::endl;
	out << "\tVertex coorditates: (" << obj.vertex.get_x() << ", " << obj.vertex.get_y() << ")" << std::endl;
	out << "\tId: " << obj.get_id() << std::endl;

	return out;
}