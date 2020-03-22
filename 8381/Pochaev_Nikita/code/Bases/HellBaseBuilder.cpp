#include "HellBaseBuilder.h"

#include "../Units/Creatures/Heck.h"
#include "../Units/Creatures/Ifrit.h"
#include "../Units/Creatures/Succubus.h"
#include "../Units/Creatures/Demon.h"
#include "../Units/Creatures/Cerberus.h"

void HellBaseBuilder::buildFabric()
{
    base->registerNewUnitType<Heck>("Cannon fodder");
    base->registerNewUnitType<Ifrit>("Infantry");
    base->registerNewUnitType<Succubus>("Shooter");
    base->registerNewUnitType<Demon>("Wizard");
    base->registerNewUnitType<Cerberus>("Cavalry");
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
