#include "thief.h"

using namespace unit;


Thief::Thief(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    GroundUnit(point, mediator)
{
    healthPoints = 50;
}


size_t Thief::farm() const
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
    return std::make_shared<Thief>(*this);
}


char Thief::draw() const
{
    return 'T';
}
