#include "armorupdatelogic.hpp"

void ArmorUpdateLogic::updateUnit(std::shared_ptr<Unit> unit) const
{
    unit->setArmor(this->armor->clone());
}
