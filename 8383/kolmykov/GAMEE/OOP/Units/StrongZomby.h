#pragma once
#include "FatZomby.h"
#include "StrongNearAttack.h"
#include "StrongArm.h"

class StrongZomby :
	public FatZomby
{
public:
	StrongZomby();
    StrongZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	StrongZomby(int x, int y, int level);
	StrongZomby(const StrongZomby& other);
	StrongZomby(StrongZomby&& other);
	StrongZomby& operator=(const StrongZomby& other);
	StrongZomby& operator=(StrongZomby&& other);
	~StrongZomby();
	char getChar();
    std::string getPath();
};

