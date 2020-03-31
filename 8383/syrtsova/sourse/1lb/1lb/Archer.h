#pragma once
#include "Classes.h"

class Archer : public Classe_archer
{
	int hope;
public:
	void hail_of_arrows();
	void double_shot();
	void poison_arrow();
	Archer(int &x, int &y);
	~Archer();
};


class Arbalester : public Classe_archer
{
	int intuition;
public:
	void reliable_shot();
	void crossbow_shot();
	void fire_shot();
	Arbalester(int &x, int &y);
	~Arbalester();
};





