#include "DamageMediator.h"

void DamageMediator::setObject1(Object* obj)
{
    obj1 = obj;
}

void DamageMediator::setObject2(Object* obj)
{
    obj2 = obj;
}

void DamageMediator::attack(Object* obj) const
{
    if (!(obj1 && obj2))
        return;

    if (obj == obj1)
        obj2->getDamage(obj->damage());
    else if (obj == obj2)
        obj1->getDamage(obj->damage());
}
