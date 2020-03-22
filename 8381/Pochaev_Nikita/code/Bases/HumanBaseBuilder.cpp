#include "HumanBaseBuilder.h"

#include "../Units/Creatures/Peasant.h"
#include "../Units/Creatures/Swordsman.h"
#include "../Units/Creatures/Archer.h"
#include "../Units/Creatures/Magician.h"
#include "../Units/Creatures/Knight.h"

void HumanBaseBuilder::buildFabric()
{
    base->registerNewUnitType<Peasant>("Cannon fodder");
    base->registerNewUnitType<Swordsman>("Infantry");
    base->registerNewUnitType<Archer>("Shooter");
    base->registerNewUnitType<Magician>("Wizard");
    base->registerNewUnitType<Knight>("Cavalry");
}

void HumanBaseBuilder::buildUnitCount()
{
    base->initUnitCount();
}

std::shared_ptr<GameBase> HumanBaseBuilder::getBase()
{
    return base;
}

void HumanBaseBuilder::createNewBase()
{
    base.reset(new HumanBase);
}