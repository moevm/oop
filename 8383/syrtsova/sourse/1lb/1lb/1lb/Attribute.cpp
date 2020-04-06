#include "pch.h"
#include "Attribute.h"
#include <iostream>

Health::Health() {}
Health::Health(int h) : health(h) {}
int Health::returnHealth(){
	return health;
}

void Health::change(int shift)
{
	if (health == max_health)
		return;
	health += shift;
	if (health <= 0)
		delete this;
}

void Health::setAtrib(int h)
{
	health = h;
	max_health = health;
}

Health::~Health()
{
	std::cout << std::endl << "Критический урон!";
}


Armor::Armor() {}
Armor::Armor(int a) : armor (a) {}
int Armor::returnArmor(){
	return armor;
}
void Armor::setAtrib(int a)
{
	armor = a;
}

void Armor::change(int shift)
{
	armor += shift;
	if (armor <= 0)
		armor = 0;
}


Armor::~Armor() {}

Attack::Attack() {}
Attack::Attack(int a) : attack(a) {}
int Attack::returnAttack(){
	return attack;
}
void Attack::setAtrib(int a)
{
	attack = a;
}
void Attack::change(int shift)
{
	attack += shift;
	if (attack <= 0)
		attack = 0;
}
Attack::~Attack() {}

Radius::Radius() {}
Radius::Radius(int r) : radius(r) {}
int Radius::returnRadius(){
	return radius;
}
void Radius::setAtrib(int r)
{
	 radius = r;
}
Radius::~Radius() {}


Name::Name() {}
Name::Name(char n) : name(n) {}
char Name::returnName() {
	return name;
}
void Name::setAtrib(int n)
{
	name = n;
}
Name::~Name() {}
