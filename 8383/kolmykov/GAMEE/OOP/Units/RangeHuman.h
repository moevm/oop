#pragma once
#include "Human.h"
#include "LiteArmor.h"
#include "CommonHumanMove.h"
class RangeHuman :
	public Human
{
public:
	RangeHuman();
    RangeHuman(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	RangeHuman(int x, int y, int level);
	RangeHuman(const RangeHuman& other);
	RangeHuman(RangeHuman&& other);
	RangeHuman& operator=(const RangeHuman& other);
	RangeHuman& operator=(RangeHuman&& other);
	virtual ~RangeHuman() = 0;
	virtual char getChar();
};

