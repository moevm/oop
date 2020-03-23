#include "noobject.h"


NoObject::NoObject()
{
    strategy = nullptr;
}

NoObject::~NoObject()
{
    delete strategy;
}

char NoObject::draw()
{
    return '\0';
}


void NoObject::selectStrategy(Unit *unit)
{
    Q_UNUSED(unit);

    strategy = new NoStrategy;
}


NoObject* NoObject::clone()
{
    NoObject* object = new NoObject;
    if (strategy) {
        object->strategy = this->strategy->clone();
    }
    return  object;
}


