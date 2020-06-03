#include "Object.h"
#include "Unit.h"

Unit::~Unit(){}

void Unit::Print() {
	cout << "ОПИСАНИЕ ПЕРСОНАЖА:\n";
	cout << "Имя: " << name << "\n";
	cout << "Здоровье: " << health << " единиц.\n";
	cout << "Урон: " << damage << " единиц.\n";
	cout << "Броня: " << armor << " единиц.\n";
}

Hero::Hero(int damage, int armor, char symbol, int view) {
	this->damage = damage;
	health = 500;
	this->armor = armor;
	setName(symbol);
	setView(view);
}

Healer::Healer() :Hero(200, 100, (char)3, 3) {}		// вызов конструктора базового класса

Magician::Magician() : Hero(600, 300, (char)15, 4) {}

Monster::Monster(int damage, int armor, char symbol, int view) {
	this->damage = damage;
	health = 1000;
	this->armor = armor;
	setName(symbol);
	setView(view);
}

Vampire::Vampire() :Monster(450, 400, (char)2, 1) {}

Werewolf::Werewolf() : Monster(650, 500, (char)4, 2) {}

People::People(int damage, int armor, char symbol, int view) {
	this->damage = damage;
	health = 200;
	this->armor = armor;
	setName(symbol);
	setView(view);
}

Hunter::Hunter() :People(300, 150, (char)6, 5) {}

Man::Man() : People(150, 50, (char)1, 6) {}