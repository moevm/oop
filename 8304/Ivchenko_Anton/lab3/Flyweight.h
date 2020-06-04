#pragma once

#include "Damage.h"
#include "Armor.h"
#include <map>


class Atributes {
private:
	Damage* damage;
	Armor* armor;
	int speed;
public:
	Atributes() {};
	Atributes(int a, int b, int c) {
		
		damage = new Damage(a);
		armor = new Armor(b);
		speed = c;

	}
	Damage* getDamage() {
		return damage;
	}
	Armor* getArmor() {
		return armor;
	}
	int getSpeed() {
		return speed;
	}
	~Atributes() {};

};
class TypeOfUnit {

private:
	std::map <char, Atributes*> my_map;
public:
	TypeOfUnit();
	Atributes* getType(char a);
	~TypeOfUnit() {};
};
