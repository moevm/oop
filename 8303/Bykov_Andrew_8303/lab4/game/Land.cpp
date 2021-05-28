#include "Land.h"
#include "Base.h"
#include <string>
void Land::slow(Unit * unit, float debuff)
{
	unit->debuffStamina(debuff);
}
void Land::weak(Unit * unit, float debuff)
{
	unit->debuffAttack(debuff);
}
void Land::disableAttack(Unit * unit)
{
	unit->enableAttack(false);
}
void Land::enableAttack(Unit * unit)
{
	unit->enableAttack(true);
}


void RiverProxy ::interact(Unit * unit)
{
	if (unit->getClass() == "Infantry" || unit->getClass() == "Archers")
	{
		land->disableAttack(unit);
		land->slow(unit, 0.5);
	}
}
void ForestProxy::interact(Unit * unit)
{
	if (unit->getClass() == "Archers")
		land->disableAttack(unit);
	if (unit->getClass() == "Cavalry")
	{
		land->enableAttack(unit);
		land->slow(unit, 0.75);
	}
	if (unit->getClass() == "Infantry")
		land->enableAttack(unit);

}
void SwampProxy ::interact(Unit * unit)
{	
	if (unit->getClass() == "Archers" || unit->getClass() == "Cavalry" || unit->getClass() == "Infantry")
	{
		land->slow(unit, 0.25);
		land->enableAttack(unit);
		land->weak(unit, 0.5);
	}

}
void MeadowProxy::interact(Unit * unit)
{
	if (unit->getClass() == "Archers" || unit->getClass() == "Cavalry" || unit->getClass() == "Infantry")
	{
		land->slow(unit, 1);
		land->weak(unit, 1);
		land->enableAttack(unit);
	}

}
void BuildingProxy::interact(Unit * unit)
{

}
bool RiverProxy ::isInteract(Unit * unit)
{
	if (unit->getClass() == "Cavalry")
		return false;
	return true;
}
bool ForestProxy::isInteract(Unit * unit)
{
	return true;
}
bool SwampProxy ::isInteract(Unit * unit)
{
	return true;
}
bool MeadowProxy::isInteract(Unit * unit)
{
	return true;
}
bool BuildingProxy::isInteract(Unit * unit)
{
	return false;
}

void Trap::operator>>(Unit * unit)
{
	if (unit->getClass() == "Infantry")
	{
		it = new Interactor(new Infantry_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Archers")
	{
		it = new Interactor(new Archers_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Cavalry")
	{
		it = new Interactor(new Cavalry_Iteraction);
		it->interact(unit);
	}
}
void Trap::Archers_Iteraction::interact(Unit * unit)
{
	unit->setNumber(0);
}
void Trap::Cavalry_Iteraction::interact(Unit * unit)
{
	unit->setNumber(int(unit->getNumber() * 0.5));
}
void Trap::Infantry_Iteraction::interact(Unit * unit)
{
	unit->setNumber(int(unit->getNumber() * 0.25));
}


void Gold::operator>>(Unit * unit)
{
	if (unit->getClass() == "Infantry")
	{
		it = new Interactor(new Infantry_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Archers")
	{
		it = new Interactor(new Archers_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Cavalry")
	{
		it = new Interactor(new Cavalry_Iteraction);
		it->interact(unit);
	}
}
void Gold::Archers_Iteraction::interact(Unit * unit)
{
	srand(int(time(0)));
	unit->getBase()->addGold(rand()%1000 + 1);
}
void Gold::Cavalry_Iteraction::interact(Unit * unit)
{
	srand(int(time(0)));
	unit->getBase()->addGold(rand() % 1000 + 1);
}
void Gold::Infantry_Iteraction::interact(Unit * unit)
{
	srand(int(time(0)));
	unit->getBase()->addGold(rand() % 1000 + 1);
}

void Rune::operator>>(Unit * unit)
{
	if (unit->getClass() == "Infantry")
	{
		it = new Interactor(new Infantry_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Archers")
	{
		it = new Interactor(new Archers_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Cavalry")
	{
		it = new Interactor(new Cavalry_Iteraction);
		it->interact(unit);
	}
}
void Rune::Archers_Iteraction::interact(Unit * unit)
{
	unit->debuffAttack(1.5);
}
void Rune::Cavalry_Iteraction::interact(Unit * unit)
{
	unit->debuffStamina(1.5);
}
void Rune::Infantry_Iteraction::interact(Unit * unit)
{
	unit->debuffArmor(1.5);
}

void Curse::operator>>(Unit * unit)
{
	if (unit->getClass() == "Infantry")
	{
		it = new Interactor(new Infantry_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Archers")
	{
		it = new Interactor(new Archers_Iteraction);
		it->interact(unit);
	}
	if (unit->getClass() == "Cavalry")
	{
		it = new Interactor(new Cavalry_Iteraction);
		it->interact(unit);
	}
}
void Curse::Archers_Iteraction::interact(Unit * unit)
{
	unit->debuffAttack(0.5);
}
void Curse::Cavalry_Iteraction::interact(Unit * unit)
{
	unit->debuffStamina(0.5);
}
void Curse::Infantry_Iteraction::interact(Unit * unit)
{
	unit->debuffArmor(0.5);
}