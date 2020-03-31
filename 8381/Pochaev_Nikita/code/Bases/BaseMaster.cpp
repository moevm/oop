#include "BaseMaster.h"

void BaseMaster::setBaseBuilder(BaseBuilder *baseBuilder_)
{
    baseBuilder = baseBuilder_;
}

std::shared_ptr<GameBase> BaseMaster::getBase()
{
    return baseBuilder->getBase();
}

void BaseMaster::constructBase()
{
    baseBuilder->createNewBase();
    baseBuilder->buildFabric();
    baseBuilder->buildUnitCount();
}
