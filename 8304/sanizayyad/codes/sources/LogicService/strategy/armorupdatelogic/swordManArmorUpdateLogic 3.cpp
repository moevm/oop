 #include "SwordManArmorUpdateLogic.hpp"


void SwordManArmorUpdateLogic::updateUnit(std::shared_ptr<Unit> unit) const
{
    LightArmorFactory factory;
    unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> SwordManArmorUpdateLogic::clone() const
{
    return std::make_shared<SwordManArmorUpdateLogic>();
}
