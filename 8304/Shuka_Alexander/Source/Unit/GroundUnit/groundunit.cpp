#include "groundunit.h"


GroundUnit::GroundUnit(const Point2D& point) : Unit(point)
{

}


GroundUnit::GroundUnit(const GroundUnit& unit) : Unit(unit)
{

}


Point2D GroundUnit::moveLeft()
{
    position.x--;

    return position;
}


Point2D GroundUnit::moveRight()
{
    position.x++;

    return position;
}


Point2D GroundUnit::moveTop()
{
    position.y--;

    return position;
}


Point2D GroundUnit::moveBottom()
{
    position.y++;

    return position;
}


bool GroundUnit::isFly() const
{
    return false;
}
