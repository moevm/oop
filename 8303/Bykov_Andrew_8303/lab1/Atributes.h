#pragma once
class Physical
{
public:
	int max_health;
	int health;
	int stamina;
	void kill();
	void heal();
	void setMaxHealth(int H);

	
	

};

class Weapon
{
public:
	int attack;
	int armor;
	int range;
};

class Spirit
{
public:
	int mood;
	bool imperator_presence;
	int team;
};

