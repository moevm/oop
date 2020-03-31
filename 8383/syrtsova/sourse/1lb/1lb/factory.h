#include "Warrior.h"
#include "Warlock.h"
#include "Archer.h"
#include "Map.h"
//Абстрактная фабрика для производства 

class Factory
{
public:
	virtual Swordsman* createSwordsman(Map *field) = 0;
	virtual Spear* createSpear(Map *field) = 0;
	virtual Magician* createMagician(Map *field) = 0;
	virtual Healer* createHealer(Map *field) = 0;
	virtual Archer* createArcher(Map *field) = 0;
	virtual Arbalester* createArbalester(Map *field) = 0;
};
