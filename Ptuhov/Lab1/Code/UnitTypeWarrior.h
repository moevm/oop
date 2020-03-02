#pragma once
#include "UnitBase.h"
#include <random>

struct UnitTypeWarrior : public UnitBase
{
	UnitTypeWarrior() = default;
};

struct Spearman : public UnitTypeWarrior
{
	Spearman();
};

struct Shielder : public UnitTypeWarrior
{
	Shielder();
	takeDamageResult takeDamage(size_t damageSize);
};