#include "killerobject.h"


KillerObject::KillerObject()
{
    strategy = nullptr;
}


KillerObject::~KillerObject()
{
    delete strategy;
}


char KillerObject::draw()
{
    return 'x';
}


void KillerObject::selectStrategy(Unit* unit)
{
    Q_UNUSED(unit);

    strategy = new KillerStrategy;
}


KillerObject *KillerObject::clone()
{
    KillerObject* object = new KillerObject;
    if (strategy) {
        object->strategy = this->strategy->clone();
    }
    return  object;
}

