#include "Unit.h"

Unit::~Unit() {}

Unit& Unit::operator -= (Unit& unit2) { //атака
	if (unit2.getArmor() >= this->getDamage()) {
		unit2.setArmor(unit2.getArmor() - (this->getDamage())); //броня уменьшается на урон другого юнита
	}
	else {
		unit2.setHealth(unit2.getHealth() - (this->getDamage()));//проверяем в другом месте не отрицательное ли здоровье == смерть
	}
	return *this;
}

Hero::Hero(char symbol, int view) {
	_damage.newSetValue(500);
	_health.setValue(view);
	_armor.setValue(view);
	setName(symbol);
	setView(view);
}

Healer::Healer() :Hero((char)3, 3) {}		// вызов конструктора базового класса

Magician::Magician() : Hero((char)15, 4) {}

Monster::Monster(char symbol, int view) {
	_damage.setValue(view);
	_health.newSetValue(1000);
	_armor.setValue(view);
	setName(symbol);
	setView(view);
}

Vampire::Vampire() :Monster((char)2, 1) {}

Werewolf::Werewolf() : Monster((char)4, 2) {}

People::People(char symbol, int view) {
	_damage.setValue(view);
	_health.setValue(view);
	_armor.setValue(view);
	setName(symbol);
	setView(view);
}

Hunter::Hunter() :People((char)6, 5) {}

Man::Man() : People((char)1, 6) {}