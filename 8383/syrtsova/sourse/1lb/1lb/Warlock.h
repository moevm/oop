#pragma once
#include "Classes.h"

class Magician : public Classe_warlock
{
private: 
	int ether;

public:
	void meteorite();
	void fiery_ray();
	void storm();
	Magician(int &x, int &y);
	~Magician();
};


class Healer : public Classe_warlock
{
	int prayer;
public:
	void heal();
	void mass_hill();
	void cover();
	Healer(int &x, int &y);
	~Healer();
};




