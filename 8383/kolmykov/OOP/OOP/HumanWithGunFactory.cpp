#include "HumanWithGunFactory.h"



HumanWithGunFactory::HumanWithGunFactory()
{
	type = UnitType::HUMAN_WITH_GUN;
}


HumanWithGunFactory::~HumanWithGunFactory()
{
}

std::shared_ptr<Unit> HumanWithGunFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanWithGun(x, y, level));
}
