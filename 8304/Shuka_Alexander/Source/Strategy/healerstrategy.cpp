#include "healerstrategy.h"

using namespace unit;


void HealerStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    unit->toHurt(-100);
}


std::shared_ptr<Strategy> HealerStrategy::clone() const
{
    return std::make_shared<HealerStrategy>();
}
