#include "neutralobj.h"
#include <iostream>
char Neutral::getName()
{
    return this->name;
}
void FieldMine::operator>>(Unit *unit)
{
    if(unit->getClassName() == "Trooper")
    {
        i = new Interactor(new TrooperIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Droid")
    {
        i = new Interactor(new DroidIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Tank")
    {
        i = new Interactor(new TankIt);
        i->interact(unit);
    }
}

void FieldMine::TrooperIt::interact(Unit *unit)
{
    unit->buffHealth(0.3);
    unit->buffArmor(0.5);
}
void FieldMine::DroidIt::interact(Unit *unit)
{
    unit->buffHealth(0.9);
    unit->buffArmor(0.4);
}
void FieldMine::TankIt::interact(Unit *unit)
{
    unit->buffHealth(0.5);
    unit->buffArmor(0.7);
}

void Village::operator>>(Unit *unit)
{
    if(unit->getClassName() == "Human")
    {
        i = new Interactor(new TrooperIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Droid")
    {
        i = new Interactor(new DroidIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Tank")
    {
        i = new Interactor(new TankIt);
        i->interact(unit);
    }
}

void Village::TrooperIt::interact(Unit *unit)
{
    unit->buffHealth(1.5);
}

void Village::DroidIt::interact(Unit *unit)
{
    unit->buffHealth(1.2);
}

void Village::TankIt::interact(Unit *unit)
{
    unit->buffHealth(1.2);
}

void Workshop::operator>>(Unit *unit)
{
    if(unit->getClassName() == "Human")
    {
        i = new Interactor(new TrooperIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Droid")
    {
        i = new Interactor(new DroidIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Tank")
    {
        i = new Interactor(new TankIt);
        i->interact(unit);
    }
}

void Workshop::TrooperIt::interact(Unit *unit)
{
    unit->buffArmor(1.3);
}

void Workshop::DroidIt::interact(Unit *unit)
{
    unit->buffArmor(1.4);
}

void Workshop::TankIt::interact(Unit *unit)
{
    unit->buffArmor(1.4);
}

void Altar::operator>>(Unit *unit)
{
    if(unit->getClassName() == "Human")
    {
        i = new Interactor(new TrooperIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Droid")
    {
        i = new Interactor(new DroidIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Tank")
    {
        i = new Interactor(new TankIt);
        i->interact(unit);
    }
}

void Altar::TrooperIt::interact(Unit *unit)
{
    unit->buffAttack(1.5);
}

void Altar::DroidIt::interact(Unit *unit)
{
    unit->buffAttack(1.5);
}

void Altar::TankIt::interact(Unit *unit)
{
    unit->buffAttack(1.2);
}

void NoneObject::operator>>(Unit * unit)
{
    if(unit->getClassName() == "Human")
    {
        i = new Interactor(new TrooperIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Droid")
    {
        i = new Interactor(new DroidIt);
        i->interact(unit);
    }
    if(unit->getClassName() == "Tank")
    {
        i = new Interactor(new TankIt);
        i->interact(unit);
    }
}

void NoneObject::TrooperIt::interact(Unit *unit)
{
    return;
}

void NoneObject::DroidIt::interact(Unit *unit)
{
    return;
}

void NoneObject::TankIt::interact(Unit *unit)
{
    return;
}
