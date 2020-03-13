#include "groundunit.h"

using namespace unit;


GroundUnit::GroundUnit(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    Unit(point, mediator)
{

}


GroundUnit::GroundUnit(const GroundUnit& unit) : Unit(unit)
{

}


bool GroundUnit::moveLeft()
{
    bool result = mediator->notify(shared_from_this(), MOVE_LEFT);

    if (result) {
        position.x--;
        return true;
    }

    return false;
}


bool GroundUnit::moveRight()
{
    bool result = mediator->notify(shared_from_this(), MOVE_RIGHT);

    if (result) {
        position.x++;
        return true;
    }

    return false;
}


bool GroundUnit::moveTop()
{
    bool result = mediator->notify(shared_from_this(), MOVE_TOP);

    if (result) {
        position.y--;
        return true;
    }

    return false;
}


bool GroundUnit::moveBottom()
{
    bool result = mediator->notify(shared_from_this(), MOVE_BOTTOM);

    if (result) {
        position.y++;
        return true;
    }

    return false;
}


bool GroundUnit::isFly() const
{
    return false;
}
