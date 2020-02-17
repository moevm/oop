#include "warriorfactory.h"


std::shared_ptr<Unit> WarriorFactory::createUnit(const Point2D& point)
{
    std::shared_ptr<Unit> unit(new Warrior(point));

    return unit;
}
