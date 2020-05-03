#include "heallerobject.h"


HeallerObject::HeallerObject()
{
    strategy = nullptr;
}

HeallerObject::~HeallerObject()
{
    delete strategy;
}


char HeallerObject::draw()
{
    return '+';
}


void HeallerObject::selectStrategy(Unit* unit)
{
    Q_UNUSED(unit);

    strategy = new HeallerStrategy;
}


HeallerObject* HeallerObject::clone()
{
    HeallerObject* object = new HeallerObject;
    object->strategy = this->strategy->clone();
    return  object;
}
