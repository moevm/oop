#pragma once
#include "Unit.h"
class ArmyFactory
{
public:
	virtual Unit* createTank() = 0;
	virtual Unit* createDamager() = 0;
};

class WarriorFactory : public ArmyFactory
{
public:
	Unit* createTank() {
		return new WarriorTank;
	}
	Unit* createDamager() {
		return new WarriorDamager;
	}
};

class ShooterFactory : public ArmyFactory
{
public:
	Unit* createTank() {
		return new ShooterTank;
	}
	Unit* createDamager() {
		return new ShooterDamager;
	}
};

class BufferFactory : public ArmyFactory
{
public:
	Buffer* createTank() {
		return new BufferTank;
	}
	Buffer* createDamager() {
		return new BufferDamager;
	}
};

