#pragma once
#include "UnitType.h"
#include <memory>
#include "ObserverInterface.h"


class UnitSnapshot
{
private:
	UnitType type;
	int hp;
	int maxHP;
	int ownArmor;
	int ownDamage;
	bool visability;
	int level;
	int landDamage;
	int landDefence;
	int observerSize;
	int observerCount;
	int coordX;
	int coordY;
	std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers;
public:
	UnitSnapshot(UnitType type, int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY);
	~UnitSnapshot();
	int getType();
	int getHP();
	int getMaxHP();
	int getOwnArmor();
	int getOwnDamage();
	bool getVisability();
	int getLevel();
	int getLandDamage();
	int getLandDefence();
	std::shared_ptr<std::shared_ptr<ObserverInterface>[]> getObservers();
	int getObserverSize();
	int getObserverCount();
	int getCoordX();
	int getCoordY();
};

