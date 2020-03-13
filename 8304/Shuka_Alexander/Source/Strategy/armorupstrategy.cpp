#include "armorupstrategy.h"

using namespace unit;


void ArmorUpStrategy::changeUnit(std::shared_ptr<Unit>& unit)
{
    unit->setArmor(this->armor->clone());
}
