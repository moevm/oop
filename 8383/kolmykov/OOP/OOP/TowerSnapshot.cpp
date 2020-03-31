#include "TowerSnapshot.h"


TowerSnapshot::TowerSnapshot(int level, int hp, int damage, int size, int unitCount, std::shared_ptr<UnitFactory> factory)
:level(level), hp(hp), damage(damage), size(size), unitCount(unitCount), factory(factory){

}

TowerSnapshot::~TowerSnapshot()
{
}

int TowerSnapshot::getLevel()
{
	return level;
}

int TowerSnapshot::getHP()
{
	return hp;
}

int TowerSnapshot::getDamage()
{
	return damage;
}

int TowerSnapshot::getSize()
{
	return size;
}

int TowerSnapshot::getUnitCount()
{
	return unitCount;
}

std::shared_ptr<UnitFactory> TowerSnapshot::getFactory()
{
	return factory;
}
