#include "Warrior.h"
#include "Warlock.h"
#include "Archer.h"
#include "Map.h"
//Абстрактная фабрика для производства 

class Factory
{
public:
	virtual Swordsman* createSwordsman(Map* field) = 0;
	virtual Spear* createSpear(Map* field) = 0;
	virtual Magician* createMagician(Map* field) = 0;
	virtual Healer* createHealer(Map* field) = 0;
	virtual Archer* createArcher(Map* field) = 0;
	virtual Arbalester* createArbalester(Map* field) = 0;
};


/*
// Класс, содержащий всех воинов той или иной армии
class Army
{
public:
	~Army() {
		int i;
		for (i = 0; i < vi.size(); ++i)  delete vi[i];
		for (i = 0; i < va.size(); ++i)  delete va[i];
		for (i = 0; i < vh.size(); ++i)  delete vh[i];
	}
	void info() {
		int i;
		for (i = 0; i < vi.size(); ++i)  vi[i]->info();
		for (i = 0; i < va.size(); ++i)  va[i]->info();
		for (i = 0; i < vh.size(); ++i)  vh[i]->info();
	}
	vector<Warrlock*> vi;
	vector<Archer*> va;
	vector<Warior*> vh;
};

// Здесь создается армия той или иной стороны
class Game
{
public:
	Army* createArmy(ArmyFactory& factory) {
		Army* p = new Army;
		p->vi.push_back(factory.createWarrlock());
		p->va.push_back(factory.createArcher());
		p->vh.push_back(factory.createWarior());
		return p;
	}
};*/