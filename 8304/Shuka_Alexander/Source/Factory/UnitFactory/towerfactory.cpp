#include "towerfactory.h"


std::shared_ptr<Unit> TowerFactory::createUnit(const Point2D& point)
{
    std::shared_ptr<Unit> unit(new Tower(point));

    return unit;
}
