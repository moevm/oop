#include "dragonarmorupstrategy.h"

using namespace unit;


void DragonArmorUpStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    HeavyArmorFactory factory;
    unit->setArmor(factory.createArmor());
}


std::shared_ptr<Strategy> DragonArmorUpStrategy::clone() const
{
    return std::make_shared<DragonArmorUpStrategy>();
}
