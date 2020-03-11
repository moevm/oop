#include "tower.h"


Tower::Tower(const Point2D& point) : StandingUnit(point)
{
    healthPoints = 100;
}


size_t Tower::farm()
{
    return NO_GOLD;
}


Tower::Tower(const Tower& unit) : StandingUnit(unit)
{
    this->doCopy(unit);
}


Tower& Tower::operator=(const Tower& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


std::shared_ptr<Unit> Tower::clone()
{
    std::shared_ptr<Unit> unit(new Tower(*this));
    return unit;
}
