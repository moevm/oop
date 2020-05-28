#include "archerArmorUpdateLogic.hpp"


void ArcherArmorUpdateLogic::updateUnit(std::shared_ptr<Unit> unit) const
{
   LightArmorFactory factory;
   unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> ArcherArmorUpdateLogic::clone() const
{
    return std::make_shared<ArcherArmorUpdateLogic>();
}
