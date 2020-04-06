#include "pch.h"
#include "Classes.h"
#include "Units.h"



Classe_warrior::Classe_warrior(char N, const int &ar, const int &at, const int &f) : Units(N, 100, ar, at, 1)
{
	force = f;
}
void Classe_warrior::skill_berserk()
{
	if (force >= 10)
	{
		cout << endl << "¬оин приходит в €рость. ¬се характеристики увеличены, но ему приходитс€ платить за это кровью.";
		this->health.change(-3);
		force -= 10;
		this->armor.change(5);
		this->attack.change(4);
		this->force + 5;
		this->health.change(-5);
	}
}
Classe_warrior::~Classe_warrior()
{}

Classe_archer::Classe_archer(char N, const int &h, const int &at, const int &r, const int &ar) : Units(N, h, 20, at, r)
{
	arrows = ar;
}
void Classe_archer::skill_headshot(Units* unit)
{
	if (arrows >= 8)
	{
		cout << endl << "“очное попадание стрелой в голову соперника!";
		unit->health.change(-5);
		arrows -= 8;
	}
}
Classe_archer::~Classe_archer()
{}

Classe_warlock::Classe_warlock(char N, const int &h, const int &ar, const int &r, const int &m) : Units(N, h, ar, 1, r)
{
	mana = m;
}
void Classe_warlock::skill_fireball(Units* unit)
{
	if (mana >= 5)
	{
		cout << endl << "ѕо€вл€ютс€ три огненных шара, они способны испепелить врага";
		unit->health.change(-3);
		mana -= 5;
	}
}

Classe_warlock::~Classe_warlock()
{}

