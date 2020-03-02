#include "UnitBase.h"

takeDamageResult UnitBase::takeDamage(size_t damageSize)
{
	if (damageSize >= hp)
	{
		hp = 0;
		return takeDamageResult::death;
	}

	hp -= damageSize;
	return takeDamageResult::damageTaken;
}
