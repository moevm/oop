#pragma once
#include "SpitZomby.h"
#include "SpitToEnemyAttack.h"
#include "NoArmor.h"
#include "SpittingToEnemyHead.h"


class SpitToEnemyZomby :
	public SpitZomby
{
public:
	SpitToEnemyZomby();
    SpitToEnemyZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	SpitToEnemyZomby(int x, int y, int level);
	SpitToEnemyZomby(const SpitToEnemyZomby& other);
	SpitToEnemyZomby(SpitToEnemyZomby&& other);
	SpitToEnemyZomby& operator=(const SpitToEnemyZomby& other);
	SpitToEnemyZomby& operator=(SpitToEnemyZomby&& other);
	~SpitToEnemyZomby();
	char getChar();
    std::string getPath();
};

