#include "landscape.h"

void Landscape::enableMove(Unit *unit)
{
    unit->enableMovement(true);
}

void Landscape::disableMove(Unit *unit)
{
    unit->enableMovement(false);
}

void Landscape::enableAttack(Unit *unit)
{
    unit->enableAttack(true);
}

void Landscape::disableAttack(Unit *unit)
{
    unit->enableAttack(false);
}

void Landscape::buffHeal(Unit *unit, float n)
{
    unit->buffHealth(n);
}

void Landscape::buffAttack(Unit *unit, float n)
{
    unit->buffAttack(n);
}

void Landscape::swirl(Unit *unit)
{
    unit->buffAttack(0.5);
    unit->buffHealth(0.5);
    unit->buffArmor(0.5);
}

char::Landscape::getName()
{
    return this->name;
}

bool RiverProxy::isInteract(Unit * unit)
{
    if(unit->getClassName() == "Tank" || unit->getClassName() == "Droid")
        return false;
    return true;
}

void RiverProxy::interact(Unit * unit)
{
    if(isInteract(unit))
    {
        land->swirl(unit);
        land->disableMove(unit);
    }
}

bool ForestProxy ::isInteract(Unit * unit)
{
    if(unit->getClassName() == "Tank")
        return false;
    return true;
}

void ForestProxy::interact(Unit *unit)
{
    if(isInteract(unit))
    {
        if(unit->getClassName() == "Droid")
            land->buffHeal(unit, 0.8);
        land->disableAttack(unit);
    }
}

bool MountainProxy::isInteract(Unit * unit)
{
    return true;
}

void MountainProxy::interact(Unit *unit)
{
    if(isInteract(unit))
    {
        if(unit->getClassName() == "Trooper")
            land->buffHeal(unit, 0.75);
        land->disableMove(unit);
        land->disableAttack(unit);
    }
}

bool PlainProxy::isInteract(Unit *unit)
{
    return true;
}

void PlainProxy::interact(Unit *unit)
{
    if(isInteract(unit))
    {
        land->enableMove(unit);
        land->enableAttack(unit);
        land->buffHeal(unit, 1.0);
        land->buffAttack(unit, 1.0);
    }
}
