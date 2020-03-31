#include "pch.h"
#include "Warlock.h"
#include "Classes.h"

Magician::Magician(int &x, int &y) : Classe_warlock('M', 50, 6, 4, 100)
{
	XY.x = x;
	XY.y = y;
}
void Magician::fiery_ray()
{

}
void Magician::meteorite()
{}
void Magician::storm()
{}
Magician::~Magician()
{
}


Healer::Healer(int &x, int &y) : Classe_warlock('H', 40, 8, 2, 80)
{
	XY.x = x;
	XY.y = y;
}
void Healer::heal()
{
}
void Healer::mass_hill()
{}
void Healer::cover()
{}
Healer::~Healer()
{}


