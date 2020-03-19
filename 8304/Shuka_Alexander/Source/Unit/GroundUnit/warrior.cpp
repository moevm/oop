#include "warrior.h"

using namespace unit;


Warrior::Warrior(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    GroundUnit(point, mediator)
{
    healthPoints = 70;
}


size_t Warrior::farm() const
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
    return std::make_shared<Warrior>(*this);
}


char Warrior::draw() const
{
    return 'W';
}
