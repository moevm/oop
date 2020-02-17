#include "dragon.h"


Dragon::Dragon(const Point2D& point) : FlyingUnit(point)
{
    healthPoints = 150;
}


Dragon::Dragon(const Dragon& unit) : FlyingUnit(unit)
{
    this->doCopy(unit);
}


Dragon& Dragon::operator=(const Dragon& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


std::shared_ptr<Unit> Dragon::clone()
{
    std::shared_ptr<Unit> unit(new Dragon(*this));
    return unit;
}


size_t Dragon::farm()
{
    return NO_GOLD;
}
