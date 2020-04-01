#pragma once
#include "Human.h"
#include "MediumArmor.h"
#include"CommonHumanMove.h"
class MeleeHuman :
	public Human
{
public:
	MeleeHuman();
    MeleeHuman(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	MeleeHuman(int x, int y, int level);
	MeleeHuman(const MeleeHuman& other);
	MeleeHuman(MeleeHuman&& other);
	MeleeHuman& operator=(const MeleeHuman& other);
	MeleeHuman& operator=(MeleeHuman&& other);
	virtual ~MeleeHuman() = 0;
	virtual char getChar();
};

