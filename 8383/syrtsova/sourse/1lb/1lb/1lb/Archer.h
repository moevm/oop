#pragma once
#include "Classes.h"


class Archer : public Classe_archer
{
	int luck;
public:
	int  arrowscost[4] = { 10, 2, 3, 5 };
	void hail_of_arrows(Map* field);
	void double_shot(Units* unit);
	void poison_arrow(Units* unit);
	void showSkills()  override;
	void selectSkill(int ch, Map* field) override;
	Archer(int &x, int &y);
	~Archer();
};


class Arbalester : public Classe_archer
{
	int intuition;
public:
	int arrowscost[4] = { 5, 2, 3, 4 };
	void reliable_shot();
	void crossbow_shot(Units* unit);
	void fire_shot(Units* unit);
	void showSkills() override;
	void selectSkill(int ch, Map* field) override;
	Arbalester(int &x, int &y);
	~Arbalester();
};





