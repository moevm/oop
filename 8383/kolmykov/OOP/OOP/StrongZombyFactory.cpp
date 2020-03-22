#include "StrongZombyFactory.h"



StrongZombyFactory::StrongZombyFactory()
{
	type = UnitType::STRONG_ZOMBY;
}


StrongZombyFactory::~StrongZombyFactory()
{
}

std::shared_ptr<Unit> StrongZombyFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new StrongZomby(x, y, level));
}
