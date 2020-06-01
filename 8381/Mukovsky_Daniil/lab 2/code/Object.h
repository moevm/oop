#pragma once
#include "ObjectStrategy.h"


class PlayingField;

class Object : public FieldObject 
{
public:
	virtual bool isMovable() {
		return canMove;
	}
	virtual std::string getName() {
		return name;
	}
	bool isAlive() {
		return false;
	}
	//virtual void setAlive(bool flag) {}
	virtual std::string getShortName() {
		return shortName;
	}
	virtual std::string info() = 0;
	virtual FieldObject* copy() = 0;
	virtual void unitInfluence(Unit* unit) = 0;
	virtual std::string getAbstractClass() {
		return "Object";
	}
};

class HealBooster : public Object
{
public:
	HealBooster() {
		name = "Heal Booster";
		shortName = "h_b";
		canMove = false;
	}
	std::string info() {
		return "Class: HealBooster";
	}
	void unitInfluence(Unit* unit) {
		HealBoosterStrategy* strategy = new HealBoosterStrategy();
		strategy->unitInfluence(unit);
		delete strategy;
	}
	FieldObject* copy(){
		return new HealBooster(*this);
	}
};

class DamageBooster : public Object
{
public:
	DamageBooster() {
		name = "Damage Booster";
		shortName = "d_b";
		canMove = false;
	}
	std::string info() {
		return "Class: DamageBooster";
	}
	void unitInfluence(Unit* unit) {
		DamageBoosterStrategy* strategy = new DamageBoosterStrategy();
		strategy->unitInfluence(unit);
		delete strategy;
	}
	FieldObject* copy() {
		return new DamageBooster(*this);
	}
};

class ArmorBooster : public Object
{
public:
	ArmorBooster() {
		name = "Armor Booster";
		shortName = "a_b";
		canMove = false;
	}
	std::string info() {
		return "Class: ArmorBooster";
	}
	void unitInfluence(Unit* unit) {
		ArmorBoosterStrategy* strategy = new ArmorBoosterStrategy();
		strategy->unitInfluence(unit);
		delete strategy;
	}
	FieldObject* copy() {
		return new ArmorBooster(*this);
	}
};

class ArmorDebuff : public Object
{
public:
	ArmorDebuff() {
		name = "Armor Debuff";
		shortName = "a_d";
		canMove = false;
	}
	std::string info() {
		return "Class: ArmorDebuff";
	}
	void unitInfluence(Unit* unit) {
		ArmorDebuffStrategy* strategy = new ArmorDebuffStrategy();
		strategy->unitInfluence(unit);
		delete strategy;
	}
	FieldObject* copy() {
		return new ArmorDebuff(*this);
	}
};