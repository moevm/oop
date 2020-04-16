#pragma once
#include "CommonZomby.h"
#include "StinkingBody.h"
#include "StinkyAttack.h"


class StinkyZomby :
	public CommonZomby
{
public:
	StinkyZomby();
    StinkyZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	StinkyZomby(int x, int y, int level);
	StinkyZomby(const StinkyZomby& other);
	StinkyZomby(StinkyZomby&& other);
	StinkyZomby& operator=(const StinkyZomby& other);
	StinkyZomby& operator=(StinkyZomby&& other);
	~StinkyZomby();
	char getChar();
    std::string getPath();
};

