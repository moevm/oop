#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "UnitAttributes.h"
#include "observer_interfaces.h"
#include "FieldObject.h"
#include "Flyweight.h"


class Unit : public FieldObject, IUnit
{
protected:
	Flyweight* fly;
	UnitAttributes attributes;
	int number;
	static int count;
	bool curPlayer; //1 player - true, 2 player - false

public:
	Unit();
	virtual std::string info() = 0;
	virtual std::string getName();
	virtual std::string getShortName();
	virtual void unitInfluence(Unit* unit) {}
	virtual FieldObject* copy() = 0;

	void attachBase(IBase* base) { this->base = base; }
	virtual std::string getAbstractClass() {
		return "Unit";
	}

	bool isMovable() {
		return canMove;
	}
	bool isAlive() {
		if (!alive) {
			base->onUnitDestroyed(this);
		}
		return alive;
	}
	void getDamage(int damage) {
		int curHp = this->getAttributes()->getHealPoints();
		this->getAttributes()->setHealPoints(curHp - damage);
		if (curHp - damage <= 0) {
			setAlive(false);
		}
	}

	void setAlive(bool flag) {
		alive = flag;
		if (!alive) {
			base->onUnitDestroyed(this);
		}
	}

	void setFlyweight(Flyweight* flyweight_) {
		this->fly = flyweight_;
	}

	void setTeam(bool team) {
		curPlayer = team;
	}

	bool getTeam() {
		return curPlayer;
	}

	UnitAttributes* getAttributes() {
		return &attributes;
	}
	Unit& operator+=(FieldObject* object) {
		object->unitInfluence(this);
		return *this;
	}
	bool commitAttack(FieldObject* defender) {
		int range = this->getAttributes()->getRange();
		if (range <= 0) { 
			std::cout << "Unit can't attack with range 0\n";
			return false; }
		
		int damage = this->getAttributes()->getDamage();
		defender->getDamage(damage);
		return true;
	}

	bool commitHeal(FieldObject* defender) {
		int range = this->getAttributes()->getRange();
		if (range <= 0) { 
			std::cout << "Unit can't heal with range 0\n";
			return false; }
		int heal = -this->getAttributes()->getDamage();
		defender->getDamage(heal);
		return true;
	}

};

class Warrior : public Unit
{
public:
	virtual std::string info() = 0;
	virtual FieldObject* copy() =0;
};

class Shooter : public Unit
{
public:
	virtual std::string info() = 0;
	virtual FieldObject* copy() = 0;
};
class Buffer : public Unit
{
public:
	virtual std::string info() = 0;
	virtual FieldObject* copy() = 0;
};


class WarriorTank :public Warrior
{
public:
	WarriorTank();
	FieldObject* copy()
	{
		return new WarriorTank(*this);
	}
	std::string info();

};


class WarriorDamager : public Warrior
{
public:
	WarriorDamager();
	FieldObject* copy()
	{
		return new WarriorDamager(*this);
	}
	std::string info();

};


class ShooterTank :public Shooter
{
public:
	ShooterTank();
	FieldObject* copy()
	{
		return new ShooterTank(*this);
	}
	std::string info();

};


class ShooterDamager :public Shooter
{
public:
	ShooterDamager();
	FieldObject* copy()
	{
		return new ShooterDamager(*this);
	}
	std::string info();
};


class BufferTank :public Buffer
{
public:
	BufferTank();
	FieldObject* copy()
	{
		return new BufferTank(*this);
	}
	std::string info();
};

class BufferDamager :public Buffer
{
public:
	BufferDamager();
	FieldObject* copy()
	{
		return new BufferDamager(*this);
	}
	std::string info();
};

