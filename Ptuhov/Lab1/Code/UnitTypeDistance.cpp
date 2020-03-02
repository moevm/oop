#include "UnitTypeDistance.h"

Archer::Archer()
{
	range = 2;
	damage = 30;
	name = 'A';
}

Mage::Mage()
{
	range = 2;
	damage = 25;
	name = 'M';
}

takeDamageResult Mage::takeDamage(size_t damageSize)
{
	if (damageSize >= hp)
	{
		hp = 0;
		return takeDamageResult::death;
	}

	hp -= damageSize;
	return takeDamageResult::damageTaken;
}
