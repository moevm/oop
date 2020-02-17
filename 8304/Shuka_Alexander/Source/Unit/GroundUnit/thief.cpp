#include "thief.h"


Thief::Thief(const Point2D &point) : GroundUnit(point)
{
    healthPoints = 100;
}


size_t Thief::farm()
{
    return ONE_GOLD;
}


Thief::Thief(const Thief& unit) : GroundUnit(unit)
{
    this->doCopy(unit);
}


Thief& Thief::operator=(const Thief& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


std::shared_ptr<Unit> Thief::clone()
{
    std::shared_ptr<Unit> unit(new Thief(*this));
    return unit;
}
