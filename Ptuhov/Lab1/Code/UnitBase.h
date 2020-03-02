#pragma once
#include <random>
#include "Resourses.h"

struct UnitBase
{
	virtual takeDamageResult takeDamage(size_t damageSize);

	size_t damage;
	size_t hp;
	size_t range;
	char name;
	bool is_stealth = false;
};

