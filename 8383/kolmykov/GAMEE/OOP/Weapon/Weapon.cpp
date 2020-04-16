#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(const Weapon & other) {
	this->damage = other.damage;
	this->range = other.range;
}


Weapon::~Weapon()
{
}

int Weapon::getDamage()
{
	return damage;
}

int Weapon::getRange()
{
	return range;
}
