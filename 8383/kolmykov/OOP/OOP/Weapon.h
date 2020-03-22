#pragma once
class Weapon
{
protected:
	int damage;
	int range;
public:
	Weapon();
	Weapon(const Weapon& other);
	~Weapon();
	int getDamage();
	int getRange();
};

