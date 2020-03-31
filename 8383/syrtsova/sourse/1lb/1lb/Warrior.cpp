#include "pch.h"
#include "Warrior.h"
#include "Classes.h"




Swordsman::Swordsman(int &x, int &y) : Classe_warrior('F', 50, 8, 10)
{
	XY.x = x;
	XY.y = y;
}
void Swordsman::furious_strike()
{}
void Swordsman::shield_strike()
{}
void Swordsman::sweeping_blow()
{}
Swordsman::~Swordsman()
{}


Spear::Spear(int &x, int &y) : Classe_warrior('G', 40, 10, 8)
{
	XY.x = x;
	XY.y = y;
}
void Spear::exact_blow()
{}
void Spear::roll_forward()
{}
void Spear::spear_strike()
{}
Spear::~Spear()
{}


