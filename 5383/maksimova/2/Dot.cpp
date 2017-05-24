#include <cmath>
#include "Dot.h"


Dot::Dot() :x(0), y(0) {} // êîíñòðóêòîð ïî-óìîë÷àíèþ

Dot::Dot(double _x, double _y) : x(_x), y(_y) {} //êîíñòðóêòîð

double Dot::distance(const Dot &smth) const // âû÷èñëåíèå ðàññòîÿíèÿ
{
	double dx = smth.x - x;
	double dy = smth.y - y;
	return sqrt(dx*dx + dy*dy);
}

void Dot::rotate(double angle) // ìàòðèöà ïîâîðîòà
{
	double old_x = x;
	double old_y = y;

	x = old_x * cos(angle) - old_y * sin(angle);
	y = old_x * sin(angle) + old_y * cos(angle);
}
bool Dot::operator == (const Dot &smth) const {
	return (this->x == smth.x && this->y == smth.y);
}

bool Dot::operator != (const Dot &smth) const {
	return !(*this==smth);
}