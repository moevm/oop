#include "UnitTypeWarrior.h"

Spearman::Spearman()
{
	range = 1;
	damage = 45;
	name = 'E';
}

Shielder::Shielder()
{
	range = 0;
	damage = 20;
	name = 'S';
}

takeDamageResult Shielder::takeDamage(size_t damageSize)
{
	size_t blockChance = std::rand() % 4;
	if (blockChance == 0)
		return takeDamageResult::block;

	if (damageSize >= hp)
	{
		hp = 0;
		return takeDamageResult::death;
	}

	hp -= damageSize;
	return takeDamageResult::damageTaken;
}
