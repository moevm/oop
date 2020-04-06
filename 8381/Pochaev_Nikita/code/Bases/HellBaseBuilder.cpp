#include "HellBaseBuilder.h"

#include "Units/Creatures/Heck.h"
#include "Units/Creatures/Ifrit.h"
#include "Units/Creatures/Succubus.h"
#include "Units/Creatures/Demon.h"
#include "Units/Creatures/Cerberus.h"

void HellBaseBuilder::buildFabric()
{
    base->registerNewUnitType<Heck>(eUnitsType::CANNON_FODDER);
    base->registerNewUnitType<Ifrit>(eUnitsType::INFANTRY);
    base->registerNewUnitType<Succubus>(eUnitsType::SHOOTER);
    base->registerNewUnitType<Demon>(eUnitsType::WIZARD);
    base->registerNewUnitType<Cerberus>(eUnitsType::CAVALRY);
}

void HellBaseBuilder::buildUnitCount()
{
    base->initUnitCount();
}

std::shared_ptr<GameBase> HellBaseBuilder::getBase()
{
    return base;
}

void HellBaseBuilder::createNewBase()
{
    base.reset(new HellBase);
}
