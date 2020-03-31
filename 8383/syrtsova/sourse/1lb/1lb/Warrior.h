#pragma once
#include "Classes.h"

class Swordsman : public Classe_warrior
{
	int zeal;

public:
	void shield_strike();
	void sweeping_blow();
	void furious_strike();
	Swordsman(int &x, int &y);
	~Swordsman();
};

class Spear : public Classe_warrior
{
	int heat;
public:
	void spear_strike();
	void roll_forward();
	void exact_blow();
	Spear(int &x, int &y);
	~Spear();
};


