#pragma once
#include "Object.h"
#include "Unit.h"

class NeutralObject : public Object{ // абстрактный класс
protected:
	char name[2];
	int healthEffect;			//здоровье
	int damageEffect;			//урон	
public:
	NeutralObject(char name, int healthEffect, int damageEffect, int view);

	void setXY(int x, int y) override {
		this->x = x;
		this->y = y;
	}
	void setName(char symbol) override {
		name[0] = symbol;
		name[1] = '\0';
	}

	void setView(int view) override {
		this->view = view;
	}

	int getX() override {
		return x;
	}
	int getY() override {
		return y;
	}
	char* getName() override {
		return name;
	}
	int getView() override {
		return view;
	}

	virtual NeutralObject& operator += (Unit& unit) = 0; //holyCroos += Unit;
};

class HolyCross : public NeutralObject{ 
public:
	HolyCross();
	HolyCross& operator += (Unit& unit) override { //крест уменьшает здоровье у вампиров и магов на 100
		if (unit.getView() == 1 || unit.getView() == 4) {
			if (unit.getArmor() >= this->healthEffect) unit.setArmor(unit.getArmor() - (this->healthEffect));  //сначала -броня, потом -здоровье
			else unit.setHealth(unit.getHealth() - (this->healthEffect)); //проверяем в другом месте не отрицательное ли здоровье == смерть
		}
		return *this;
	}
};

class Tablet : public NeutralObject {
public:
	Tablet();
	Tablet& operator += (Unit& unit) override { //увеличивает здоровье на 150 всем
		unit.setHealth(unit.getHealth() + (this->healthEffect));
		return *this;
	}
};

class Snake : public NeutralObject {
public:
	Snake();
	Snake& operator += (Unit& unit) override { //уменьшает здоровье на 100 всем, кроме вампиров и оборотней
		if (unit.getView() != 1 && unit.getView() != 2) {
			if (unit.getArmor() >= this->healthEffect) unit.setArmor(unit.getArmor() - (this->healthEffect));  //сначала -броня, потом -здоровье
			else unit.setHealth(unit.getHealth() - (this->healthEffect));
		}
		return *this;
	}

};

class SurpriseBox : public NeutralObject { //двух видов 
	int typeBox;
public:
	SurpriseBox(int typeBox);
	SurpriseBox& operator += (Unit& unit) override { //good surprise - зависит от вида, который дается рандомно
		if (typeBox == 1) unit.setDamage(unit.getDamage() + (this->damageEffect));
		else unit.setHealth(unit.getHealth() + (this->healthEffect));
		return *this;
	}
};