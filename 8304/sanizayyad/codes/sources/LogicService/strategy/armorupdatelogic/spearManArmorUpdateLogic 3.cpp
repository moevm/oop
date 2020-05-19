#include "SpearManArmorUpdateLogic.hpp"


void SpearManArmorUpdateLogic::updateUnit(std::shared_ptr<Unit> unit) const
{
   LightArmorFactory factory;
   unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> SpearManArmorUpdateLogic::clone() const
{
    return std::make_shared<SpearManArmorUpdateLogic>();
}
