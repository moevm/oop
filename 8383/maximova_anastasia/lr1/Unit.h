#pragma once
#include <iostream>
#include "Object.h"
#include "Attribute.h"

using namespace std;

class Unit : public Object {			//абстрактный класс
protected:
	Health _health;    //здоровье
	Damage _damage;    //урон	
	Armor _armor;	   //броня

public:

	void setDamage(int newDamage) {
		_damage.newSetValue(newDamage);

	}
	void setHealth(int newHealth) {
		_health.newSetValue(newHealth);
	}

	void setArmor(int newHealth) {
		_armor.newSetValue(newHealth);
	}

	void setName(char symbol) override {
		name[0] = symbol;
		name[1] = '\0';
	}
	void setView(int view) override {
		this->view = view;
	}
	void setXY(int x, int y) override {
		this->x = x;
		this->y = y;
	}

	int getDamage() {
		return _damage.getValue();
	}

	int getHealth() {
		 return _health.getValue();
	}

	int getArmor() {
		return _armor.getValue();
	}

	char* getName() override {
		return name;
	}
	int getView() override {
		return view;
	}
	int getX() override {
		return x;
	}
	int getY() override {
		return y;
	}

	Unit& operator -= (Unit& unit2);

	virtual ~Unit() = 0;  //чисто виртуальный деструктор
};


class Hero :public Unit {		//тип № 1 -- Герой
public:
	Hero(char symbol, int view);
};

class Healer :public Hero {		//вид Целитель
public:
	Healer();		// вызов конструктора базового класса
};

class Magician :public Hero {	//вид Маг
public:
	Magician();
};


class Monster :public Unit {			//тип № 2 --  Монстр
public:
	Monster(char symbol, int view);
};

class Vampire :public Monster {		//вид Вампир
public:
	Vampire();
};

class Werewolf :public Monster {		//вид Оборотень
public:
	Werewolf();
};


class People :public Unit {			//тип Человек
public:
	People(char symbol, int view);
};

class Hunter :public People {			//вид Охотник 
public:
	Hunter();
};

class Man :public People {				//вид Обычный человек
public:
	Man();
};
