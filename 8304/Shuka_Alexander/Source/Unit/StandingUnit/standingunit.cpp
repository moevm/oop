#include "standingunit.h"


StandingUnit::StandingUnit(const Point2D& point) : Unit(point)
{

}


StandingUnit::StandingUnit(const StandingUnit& unit) : Unit(unit)
{

}


Point2D StandingUnit::moveLeft()
{
    return position;
}


Point2D StandingUnit::moveRight()
{
    return position;
}


Point2D StandingUnit::moveTop()
{
    return position;
}


Point2D StandingUnit::moveBottom()
{
    return position;
}


bool StandingUnit::isFly() const
{
    return false;
}
