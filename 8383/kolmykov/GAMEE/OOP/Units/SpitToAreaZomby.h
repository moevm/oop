#pragma once
#include "SpitZomby.h"
#include "NoArmor.h"
#include "SpitToAreaAttack.h"
#include "SpittingToAreaHead.h"


class SpitToAreaZomby :
	public SpitZomby
{
public:
	SpitToAreaZomby();
    SpitToAreaZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	SpitToAreaZomby(int x, int y, int level);
	SpitToAreaZomby(const SpitToAreaZomby& other);
	SpitToAreaZomby(SpitToAreaZomby&& other);
	SpitToAreaZomby& operator=(const SpitToAreaZomby& other);
	SpitToAreaZomby& operator=(SpitToAreaZomby&& other);
	~SpitToAreaZomby();
	char getChar();
    std::string getPath();
};

