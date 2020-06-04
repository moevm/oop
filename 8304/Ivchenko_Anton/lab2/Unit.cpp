#include "Unit.h"

TypeOfUnit* UnitMap = new TypeOfUnit;

Unit::Unit() {
	id = '0'; characteristics = nullptr;
};

void Unit::attack(Unit* a) {
	a->get_hit(characteristics->getDamage()->getDamageValue());
}
void Unit::get_hit(int damage) {
	Atributes* new_c = new Atributes (characteristics->getDamage()->getDamageValue(), characteristics->getArmor()->reduceHealth(damage), characteristics->getSpeed());
	this->changeCharactresistics(new_c);

}
void Unit::check_armor(Unit* a) {
	if (a->getCharactresistics()->getArmor() < 0)
		a->~Unit();
}
void Unit::setName(char a) {
	this->id = a;
}
void Unit::setType(char a) {
	this->type = a;
}
void Unit::setCoordinats(int x_, int y_) {
	x = x_;  y = y_;
}
char Unit::getid() {
	return id;
}
int Unit::getx() {
	return x;
}
int Unit::gety() {
	return y;
}
char Unit::getType() {
	return type;
}
Atributes* Unit::getCharactresistics() {
	return characteristics;
}
void Unit::changeCharactresistics(Atributes* a) {
	characteristics = a;

}
Unit::~Unit() {};


Warrior::Warrior() {
			this->setType('i');
			this->changeCharactresistics(UnitMap->getType(this->getType()));
		};
Warrior::~Warrior() {};


Swordman::Swordman() {

			this->setName('1');
		}
Swordman::~Swordman() {};

Spearman::Spearman() {

			this->setName('2');

		};
Spearman::~Spearman() {};



Archer::Archer() {
			this->setType('a');
			this->changeCharactresistics(UnitMap->getType(this->getType()));


		}
Archer::~Archer() {};

	
Slinger::Slinger() {

			this->setName('3');

		};
Slinger::~Slinger() {};


Bowman::Bowman() {

			this->setName('4');


		};
Bowman::~Bowman() {};

Cavalry::Cavalry() {
			this->setType('c');
			this->changeCharactresistics(UnitMap->getType(this->getType()));

		};
Cavalry::~Cavalry() {};

LightCavalry::LightCavalry() {

			this->setName('5');

		};
LightCavalry::~LightCavalry() {};



HeavyCavalry::HeavyCavalry() {

			this->setName('6');

		};
HeavyCavalry::~HeavyCavalry() {};
