#pragma once
#include "Unit.h"
#include <iostream>

class ObjectStrategy
{
public:
	virtual ~ObjectStrategy() = default;
	virtual void unitInfluence(Unit* unit) = 0;
};

class HealBoosterTankStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int hpBoost = 50;
		int curHp = unit->getAttributes()->getHealPoints();

		std::cout << "Before boost:" << unit->info() << "\n";
		unit->getAttributes()->setHealPoints(curHp+ hpBoost);
		std::cout << "After boost:" << unit->info() << "\n";

	}
};

class HealBoosterDamagerStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int hpBoost = 30;
		int curHp = unit->getAttributes()->getHealPoints();
		std::cout << "Before boost:" << unit->info() << "\n";
		unit->getAttributes()->setHealPoints(curHp + hpBoost);
		std::cout << "After boost:" << unit->info() << "\n";
	}
};

class HealBoosterStrategy : public ObjectStrategy
{
private:
	ObjectStrategy* strategy;
public:
	void unitInfluence(Unit* unit) {
		if (unit->getShortName().at(2) == 't') {
			strategy = new HealBoosterTankStrategy();
			strategy->unitInfluence(unit);
		}
		else {
			strategy = new HealBoosterDamagerStrategy();
			strategy->unitInfluence(unit);
		}
		delete strategy;
	}
};

class DamageBoosterTankStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int dmgBoost = 20;
		int curDmg = unit->getAttributes()->getDamage();
		unit->getAttributes()->setDamage(curDmg + dmgBoost);
	}
};

class DamageBoosterDamagerStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int dmgBoost = 40;
		int curDmg = unit->getAttributes()->getDamage();
		unit->getAttributes()->setDamage(curDmg + dmgBoost);
	}
};

class DamageBoosterStrategy : public ObjectStrategy
{
private:
	ObjectStrategy* strategy;
public:
	void unitInfluence(Unit* unit) {
		if (unit->getShortName().at(2) == 't') {
			strategy = new DamageBoosterTankStrategy();
			strategy->unitInfluence(unit);
		}
		else {
			strategy = new DamageBoosterDamagerStrategy();
			strategy->unitInfluence(unit);
		}
		delete strategy;
	}
};


class ArmorBoosterTankStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int armBoost = 40;
		int curArm = unit->getAttributes()->getArmorPoints();
		unit->getAttributes()->setArmorPoints(curArm + armBoost);
	}
};

class ArmorBoosterDamagerStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int armBoost = 20;
		int curArm = unit->getAttributes()->getArmorPoints();
		unit->getAttributes()->setArmorPoints(curArm + armBoost);
	}
};

class ArmorBoosterStrategy : public ObjectStrategy
{
private:
	ObjectStrategy* strategy;
public:
	void unitInfluence(Unit* unit) {
		if (unit->getShortName().at(2) == 't') {
			strategy = new ArmorBoosterTankStrategy();
			strategy->unitInfluence(unit);
		}
		else {
			strategy = new ArmorBoosterDamagerStrategy();
			strategy->unitInfluence(unit);
		}
		delete strategy;
	}
};

class ArmorDebuffTankStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int armDebuff = 30;
		int curArm = unit->getAttributes()->getArmorPoints();
		if (curArm <= armDebuff) {
			unit->getAttributes()->setArmorPoints(0);
		}
		else
			unit->getAttributes()->setArmorPoints(curArm - armDebuff);
	}
};

class ArmorDebuffDamagerStrategy : public ObjectStrategy
{
	void unitInfluence(Unit* unit) {
		int armDebuff = 20;
		int curArm = unit->getAttributes()->getArmorPoints();
		if (curArm <= armDebuff) {
			unit->getAttributes()->setArmorPoints(0);
		}
		else
			unit->getAttributes()->setArmorPoints(curArm - armDebuff);
	}
};

class ArmorDebuffStrategy : public ObjectStrategy
{
private:
	ObjectStrategy* strategy;
public:
	void unitInfluence(Unit* unit) {
		if (unit->getShortName().at(2) == 't') {
			strategy = new ArmorDebuffTankStrategy();
			strategy->unitInfluence(unit);
		}
		else {
			strategy = new ArmorDebuffDamagerStrategy();
			strategy->unitInfluence(unit);
		}
		delete strategy;
	}
};