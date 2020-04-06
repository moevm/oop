#include "HumanBaseBuilder.h"

#include "Units/Creatures/Peasant.h"
#include "Units/Creatures/Swordsman.h"
#include "Units/Creatures/Archer.h"
#include "Units/Creatures/Magician.h"
#include "Units/Creatures/Knight.h"

void HumanBaseBuilder::buildFabric()
{
    base->registerNewUnitType<Peasant>(eUnitsType::CANNON_FODDER);
    base->registerNewUnitType<Swordsman>(eUnitsType::INFANTRY);
    base->registerNewUnitType<Archer>(eUnitsType::SHOOTER);
    base->registerNewUnitType<Magician>(eUnitsType::WIZARD);
    base->registerNewUnitType<Knight>(eUnitsType::CAVALRY);
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
