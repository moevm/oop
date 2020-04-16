#pragma once
#include "ZombyUnit.h"
#include "NoArmor.h"
#include "CommonMove.h"
class CommonZomby :
	public ZombyUnit
{
public:
    CommonZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	CommonZomby();
	CommonZomby(int x, int y, int level);
	CommonZomby(const CommonZomby& other);
	CommonZomby(CommonZomby&& other);
	CommonZomby& operator=(const CommonZomby& other);
	CommonZomby& operator=(CommonZomby&& other);
	virtual ~CommonZomby();
	virtual char getChar();
};

