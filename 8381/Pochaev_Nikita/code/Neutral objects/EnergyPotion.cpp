#include "EnergyPotion.h"

void EnergyPotion::operator+=(const std::shared_ptr<Unit> &unit)
{
    unit->setExtraActionToken();
}
