#pragma once
#pragma once
#include <iostream>
using namespace std;

class Unit :public Object {			//абстрактный класс
protected:

	int health;			//здоровье
	int damage;			//урон	
	int armor;			//броня

public:
	void setName(char symbol) override {
		name[0] = symbol;
		name[1] = '\0';
	}

	void setView(int view) override {
		this->view = view;
	}

	char* getName() override {
		return name;
	};

	void setXY(int x, int y) override {
		this->x = x;
		this->y = y;
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

	virtual ~Unit() = 0;  //чисто виртуальный деструктор

	void Print();
};


class Hero :public Unit {		//тип № 1 -- Герой
public:
	Hero(int damage, int armor, char symbol, int view);
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
	Monster(int damage, int armor, char symbol, int view);
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
	People(int damage, int armor, char symbol, int view);
};

class Hunter :public People {			//вид Охотник 
public:
	Hunter();
};

class Man :public People {				//вид Обычный человек
public:
	Man();
};
