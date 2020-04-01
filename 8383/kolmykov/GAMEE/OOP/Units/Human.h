#pragma once
#include "Unit.h"
class Human :
	public Unit
{
public:
    Human(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	Human();
	Human(int x, int y, int level);
	Human(const Human& other);
	Human(Human&& other);
	Human& operator=(const Human& other);
	Human& operator=(Human&& other);
	virtual ~Human();
	virtual char getChar();
};

