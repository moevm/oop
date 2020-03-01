
#include "Unit/archer.h"
#include "Weapon/weapon.h"


Archer::Archer(Mediator* mediator)
{
    armor = new HeavyArmor;
    weapon = new Bow;
    health = HIGH_HEALTH_VALUE;
    coordinate = new Point2D;

    this->mediator = mediator;
}


Archer::~Archer()
{
    delete armor;
    delete weapon;
    delete coordinate;
}


void Archer::regeneration()
{
    this->health += LOW_REGENERATION_ABILITY;
}


Unit* Archer::clone()
{
    //nemnogo kostyl
    Archer* archer = new Archer(this->mediator);
    archer->armor = this->armor->clone();
    archer->weapon = this->weapon->clone();
    archer->coordinate = this->coordinate->clone();

    return archer;
}
