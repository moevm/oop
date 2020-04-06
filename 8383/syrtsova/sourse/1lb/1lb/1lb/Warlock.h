#pragma once
#include "Classes.h"


class Magician : public Classe_warlock
{
private: 
	int ether;
	int manacost[4] = { 5, 25, 45, 110 };
public:
	void selectSkill(int ch, Map* field) override;
	void showSkills() override;
	void meteorite(Units* unit);
	void ARMAGEDON(Map* field);
	void storm(Units* unit);
	Magician(int &x, int &y);
	~Magician();
};


class Healer : public Classe_warlock
{
	int prayer;
	int manacost[4] = { 5,10,25,6 };
public:
	void selectSkill(int ch, Map* field) override;
	void showSkills() override;
	void heal(Units* unit);
	void mass_heal(Map* field);
	void cover();
	Healer(int &x, int &y);
	~Healer();
};




