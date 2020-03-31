#include "LargeArmorAffectBehavior.h"



LargeArmorAffectBehavior::LargeArmorAffectBehavior()
{
}


LargeArmorAffectBehavior::~LargeArmorAffectBehavior()
{
}

void LargeArmorAffectBehavior::affectOnUnit(std::shared_ptr<Unit> unit)
{
	unit->addArmor(30);
}
