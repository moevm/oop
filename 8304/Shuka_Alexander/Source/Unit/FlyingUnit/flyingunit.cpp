#include "flyingunit.h"


FlyingUnit::FlyingUnit(const Point2D& point) : Unit(point)
{

}

FlyingUnit::FlyingUnit(const FlyingUnit& unit) : Unit(unit)
{

}


Point2D FlyingUnit::moveLeft()
{
    position.x--;

    return position;
}


Point2D FlyingUnit::moveRight()
{
    position.x++;

    return position;
}


Point2D FlyingUnit::moveTop()
{
    position.y--;

    return position;
}


Point2D FlyingUnit::moveBottom()
{
    position.y++;

    return position;
}


bool FlyingUnit::isFly() const
{
    return true;
}
