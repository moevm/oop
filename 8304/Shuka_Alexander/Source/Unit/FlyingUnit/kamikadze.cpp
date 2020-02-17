#include "kamikadze.h"


Kamikadze::Kamikadze(const Point2D& point) : FlyingUnit(point)
{
    healthPoints = 30;
}


Kamikadze::Kamikadze(const Kamikadze& unit) : FlyingUnit(unit)
{
    this->doCopy(unit);
}


Kamikadze& Kamikadze::operator=(const Kamikadze& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


size_t Kamikadze::farm()
{
    return NO_GOLD;
}


std::shared_ptr<Unit> Kamikadze::clone()
{
    std::shared_ptr<Unit> unit(new Kamikadze(*this));
    return unit;
}
