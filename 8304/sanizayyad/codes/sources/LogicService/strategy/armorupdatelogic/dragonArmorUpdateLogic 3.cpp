#include "dragonArmorUpdateLogic.hpp"

void DragonArmorUpdateLogic::updateUnit(std::shared_ptr<Unit> unit) const
{
   HeavyArmorFactory factory;
   unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> DragonArmorUpdateLogic::clone() const
{
    return std::make_shared<DragonArmorUpdateLogic>();
}
