#pragma once
#include "UnitBase.h"

struct UnitTypeStealth : public UnitBase
{
	UnitTypeStealth()
	{
		is_stealth = true;
	}
};

struct Assasin : public UnitTypeStealth
{
	Assasin()
	{
		range = 0;
		damage = 50;
		name = 'S';
	}

	takeDamageResult takeDamage(size_t damageSize)
	{
		size_t dodgeChance = std::rand() % 5;
		if (dodgeChance == 0)
			return takeDamageResult::dodge;

		if (damageSize >= hp)
		{
			hp = 0;
			return takeDamageResult::death;
		}

		hp -= damageSize;
		return takeDamageResult::damageTaken;
	}
};

struct Rogue : public UnitTypeStealth
{
	Rogue()
	{
		range = 0;
		damage = 30;
		name = 'R';
	}
};

