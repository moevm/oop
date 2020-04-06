#pragma once
#include "Units.h"


class Classe_warrior : public Units
{
protected:
	int force;
	void skill_berserk();
public:
	virtual void showSkills() = 0;
	virtual void selectSkill(int ch, Map* field) = 0;
	Classe_warrior(char N, const int &ar, const int &at, const int &f);
	~Classe_warrior();

};


class Classe_archer : public Units
{
protected:
	int arrows;
	void skill_headshot(Units* unit);
public:
	virtual void showSkills() = 0;
	virtual void selectSkill(int ch, Map* field) = 0;
	Classe_archer(char N, const int &h, const int &at, const int &r, const int &ar);
	~Classe_archer();
};

class Classe_warlock : public Units
{
protected:
	int mana;
	virtual void showSkills() = 0;
	virtual void selectSkill(int ch, Map* field) = 0;
	void skill_fireball(Units* unit);

public:
	Classe_warlock(char N, const int &h, const int &ar, const int &r, const int &m);
	~Classe_warlock();
};


