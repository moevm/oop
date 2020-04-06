#pragma once
#include "Classes.h"


class Swordsman : public Classe_warrior
{
	int zeal;
	int forcecost[4] = { 1,3,3,10 };
public:
	void shield_strike(Units* unit);
	void showSkills() override;
	void selectSkill(int ch, Map* field) override;
	void swepping_blow(Units* unit);
	void furious_strike(Units* unit);
	Swordsman(int &x, int &y);
	~Swordsman();
};

class Spear : public Classe_warrior
{
	int rage;
	int forcecost[4] = { 1,4,8,5 };
public:
	void spear_strike(Units* unit);
	void showSkills() override;
	void selectSkill(int ch, Map* field) override;
	void roll_forward(Units* unit);
	void exact_blow(Units* unit);
	Spear(int &x, int &y);
	~Spear();
};


