#pragma once
#include "CommonZomby.h"
#include "BitingHead.h"
#include "BiteAttack.h"

class BitingZomby :
	public CommonZomby
{
public:
	BitingZomby();
    BitingZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	BitingZomby(int x, int y, int level);
	BitingZomby(const BitingZomby& other);
	BitingZomby(BitingZomby&& other);
	BitingZomby& operator=(const BitingZomby& other);
	BitingZomby& operator=(BitingZomby&& other);
	~BitingZomby();
	char getChar();
    std::string getPath();
};

