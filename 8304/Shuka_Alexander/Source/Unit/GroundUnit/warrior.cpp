#include "warrior.h"


Warrior::Warrior(const Point2D& point) : GroundUnit(point)
{
    healthPoints = 100;
}


size_t Warrior::farm()
{
    return NO_GOLD;
}


Warrior::Warrior(const Warrior& unit) : GroundUnit(unit)
{
    this->doCopy(unit);
}


Warrior& Warrior::operator=(const Warrior& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


std::shared_ptr<Unit> Warrior::clone()
{
    std::shared_ptr<Unit> unit(new Warrior(*this));
    return unit;
}
