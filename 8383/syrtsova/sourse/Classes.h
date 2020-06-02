#pragma once
#include "Units.h"

/// Класс класса войнов
class Classe_warrior : public Units
{
protected:
	int force;
	void skill_berserk(Map* field, Adapter *adapter);
	virtual void showSkills(Adapter *adapter) = 0;
	virtual void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) = 0;
	Classe_warrior(char N, const int &ar, const int &at, const int &f);
	virtual ~Classe_warrior();
};

/// Класс класса лучников
class Classe_archer : public Units
{
protected:
	int arrows;
	void skill_headshot(Units* unit, Map *field, Adapter *adapter);
	virtual void showSkills(Adapter *adapter) = 0;
	virtual void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) = 0;
	Classe_archer(char N, const int &h, const int &at, const int &r, const int &ar);
	virtual ~Classe_archer();
};

/// Класс класса волшебников
class Classe_warlock : public Units
{
protected:
	int mana;
	virtual void showSkills(Adapter *adapter) = 0;
	virtual void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) = 0;
	void skill_fireball(Units* unit, Map *field, Adapter *adapter);
	Classe_warlock(char N, const int &h, const int &ar, const int &r, const int &m);
	virtual ~Classe_warlock();
};


