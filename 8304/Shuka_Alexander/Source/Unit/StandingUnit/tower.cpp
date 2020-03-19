#include "tower.h"

using namespace unit;


Tower::Tower(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    StandingUnit(point, mediator)
{
    healthPoints = 100;
}


size_t Tower::farm() const
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


char Tower::draw() const
{
    return '^';
}
