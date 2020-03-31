#include "pch.h"
#include "Classes.h"
#include "Units.h"



Classe_warrior::Classe_warrior(char N, const int &ar, const int &at, const int &f) : Units( N, 100, armor, attack, 1)
{
	force = f;
}
void Classe_warrior::skill_berserk()
{}
Classe_warrior::~Classe_warrior()
{}

Classe_archer::Classe_archer(char N, const int &h, const int &at, const int &r, const int &ar) : Units(N, health, 20, attack, radius)
{
	arrows = ar;
}
void Classe_archer::skill_headshot()
{}
Classe_archer::~Classe_archer()
{}

Classe_warlock::Classe_warlock(char N, const int &h, const int &ar, const int &r, const int &m) : Units(N, health, armor, 1, radius)
{
	mana = m;
}
void Classe_warlock::skill_fireball()
{}
Classe_warlock::~Classe_warlock()
{}

