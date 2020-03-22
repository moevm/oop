#pragma once
#include <memory>
#include "UnitFactory.h"


class TowerSnapshot
{
private:
	int level;
	int hp;
	int damage;
	int size;
	int unitCount;
	std::shared_ptr<UnitFactory> factory;
public:
	TowerSnapshot(int level, int hp, int damage, int size, int unitCount, std::shared_ptr<UnitFactory> factory);
	~TowerSnapshot();
	int getLevel();
	int getHP();
	int getDamage();
	int getSize();
	int getUnitCount();
	std::shared_ptr<UnitFactory> getFactory();
};

