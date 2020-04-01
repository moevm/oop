#pragma once
#include "ZombyUnit.h"
#include "FatZombyMoveBehavior.h"
#include "NoArmor.h"
class FatZomby :
	public ZombyUnit
{
public:
    FatZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	FatZomby();
	FatZomby(int x, int y, int level);
	FatZomby(const FatZomby& other);
	FatZomby(FatZomby&& other);
	FatZomby& operator=(const FatZomby& other);
	FatZomby& operator=(FatZomby&& other);
	virtual ~FatZomby() = 0;
	virtual char getChar();
};

