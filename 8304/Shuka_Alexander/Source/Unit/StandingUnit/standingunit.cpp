#include "standingunit.h"

using namespace unit;


StandingUnit::StandingUnit(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    Unit(point, mediator)
{

}


StandingUnit::StandingUnit(const StandingUnit& unit) : Unit(unit),
    std::enable_shared_from_this<Unit>(unit)
{

}


bool StandingUnit::moveLeft()
{
    return false;
}


bool StandingUnit::moveRight()
{
    return false;
}


bool StandingUnit::moveTop()
{
    return false;
}


bool StandingUnit::moveBottom()
{
    return false;
}


bool StandingUnit::isFly() const
{
    return false;
}
