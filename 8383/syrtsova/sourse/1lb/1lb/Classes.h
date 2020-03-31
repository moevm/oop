#pragma once
#include "Units.h"

class Classe_warrior : public Units
{
protected:
	int force;
	void skill_berserk();
public:
	Classe_warrior(char N, const int &ar, const int &at, const int &f);
	~Classe_warrior();

};


class Classe_archer : public Units
{
protected:
	int arrows;
	void skill_headshot();
public:
	Classe_archer(char N, const int &h, const int &at, const int &r, const int &ar);
	~Classe_archer();
};

class Classe_warlock : public Units
{
protected:
	int mana;
	void skill_fireball();

public:
	Classe_warlock(char N, const int &h, const int &ar, const int &r, const int &m);
	~Classe_warlock();
};


