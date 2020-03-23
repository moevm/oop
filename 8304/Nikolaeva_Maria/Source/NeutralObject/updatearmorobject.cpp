#include "updatearmorobject.h"


UpdateArmorObject::UpdateArmorObject()
{
    strategy = nullptr;
}


UpdateArmorObject::~UpdateArmorObject()
{
    delete strategy;
}

char UpdateArmorObject::draw()
{
    return '^';
}


void UpdateArmorObject::selectStrategy(Unit* unit)
{
   if (typeid (*unit) == typeid (Harpy) ||
           typeid (*unit) == typeid (Dragon)) {
       strategy = new UpdateNoArmorStrategy;
   }
   else if(typeid (*unit) == typeid (Swordsman) ||
           typeid (*unit) == typeid (Dwarf)) {
       strategy = new UpdateLightArmorStrategy;
   }
   else {
       strategy = new UpdateHeavyArmorStrategy;
   }
}


UpdateArmorObject* UpdateArmorObject::clone()
{
    UpdateArmorObject* object = new UpdateArmorObject;
    object->strategy = this->strategy->clone();
    return  object;
}
