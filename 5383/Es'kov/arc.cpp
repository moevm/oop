#include <math.h>
#include "arc.h"

arc::arc(int r, int angle_start, int angle_stop, paint_area_info paint_info) : shape(paint_info)
{
	arc_radius = r;
	arc_angle_start = angle_start - 90;
	arc_angle_stop = angle_stop - 90;

	cur_angle = 0;
	cur_ratio = 0.0f;
}

void arc::redraw()
{
	arc_radius = arc_radius * (1 + cur_ratio);
	p_info.x_center+=X;
	p_info.y_center-=Y;
	
	int v_x = p_info.x_center + arc_radius * cos(arc_angle_start * 3.1415 / 180);
	int v_y = p_info.y_center + arc_radius * sin(arc_angle_start * 3.1415 / 180);

	int new_x, new_y;

	HPEN hPen;
	hPen = CreatePen(PS_DASH, 1, RGB(p_info.color.r, p_info.color.g,
		             p_info.color.b));
	SelectObject(p_info.area_ptr, hPen);

	for(int theta = arc_angle_start + 1; theta <= arc_angle_stop; theta++)
	{
		math_rotate(p_info.x_center, p_info.y_center, v_x, v_y, cur_angle, new_x, new_y); 
		MoveToEx(p_info.area_ptr, new_x, new_y, NULL);

		v_x = p_info.x_center + arc_radius * cos(theta * 3.1415 / 180);
		v_y = p_info.y_center + arc_radius * sin(theta * 3.1415 / 180);

		math_rotate(p_info.x_center, p_info.y_center, v_x, v_y, cur_angle, new_x, new_y);
		LineTo(p_info.area_ptr, new_x, new_y);
	}
}

void arc::setXY(int x, int y)
{
	X = x;
	Y = y;
}

int arc::getX()
{
	return this->X;
}

int arc::getY()
{
	return this->Y;
}

void arc::draw(int x1, int y1)
{
	X = x1;
	Y = y1;
	redraw();
}

void arc::rotate(int angle)
{
	cur_angle = angle;
}

void arc::scale(float ratio)
{
	cur_ratio = ratio;
}

int arc::get_radius()
{
	return this->arc_radius;
}
int arc::get_start_angle()
{
	return this->arc_angle_start;
}
int arc::get_stop_angle()
{
	return this->arc_angle_stop;
}

void arc::set_radius(int r)
{
	arc_radius = r;
}
void arc::set_start_angle(int sa)
{
	arc_angle_start = sa - 90;
}
void arc::set_stop_angle(int sa)
{
	arc_angle_stop = sa - 90;
}

float arc::perimetr()
{
	return (abs(this->arc_angle_start-this->arc_angle_stop))*((this->arc_radius*3.1415)/180);
}

std::ostream& operator<<(std::ostream& os, arc& a1)
{
	os << "===ДУГА===\n" << a1.getX() << ";" << a1.getY() << "\nРадиус: " << a1.get_radius() << "\nНачало дуги: " << a1.get_start_angle() << "\nКонец дуги: " << a1.get_stop_angle() <<"\nПериметр: " << a1.perimetr();

	return os;
}