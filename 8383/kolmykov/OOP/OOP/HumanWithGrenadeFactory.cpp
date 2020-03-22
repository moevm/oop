#include "HumanWithGrenadeFactory.h"



HumanWithGrenadeFactory::HumanWithGrenadeFactory()
{
	type = UnitType::HUMAN_WITH_GRENADE;
}


HumanWithGrenadeFactory::~HumanWithGrenadeFactory()
{
}

std::shared_ptr<Unit> HumanWithGrenadeFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanWithGrenade(x, y, level));
}
