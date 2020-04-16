#pragma once
#include "ZombyUnit.h"
#include "CommonMove.h"
#include "NoArmor.h"

class SpitZomby :
	public ZombyUnit
{
public:
    SpitZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	SpitZomby();
	SpitZomby(int x, int y, int level);
	SpitZomby(const SpitZomby& other);
	SpitZomby(SpitZomby&& other);
	SpitZomby& operator=(const SpitZomby& other);
	SpitZomby& operator=(SpitZomby&& other);
	virtual ~SpitZomby() = 0;
	virtual char getChar();
};

