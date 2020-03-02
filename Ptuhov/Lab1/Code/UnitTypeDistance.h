#pragma once
#include "UnitBase.h"

struct UnitTypeDistance : public UnitBase
{
	UnitTypeDistance() = default;
};

struct Archer : public UnitTypeDistance
{
	Archer();
};

struct Mage : public UnitTypeDistance
{
	Mage();
	takeDamageResult takeDamage(size_t damageSize);
};