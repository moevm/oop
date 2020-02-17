#include "dragonfactory.h"


std::shared_ptr<Unit> DragonFactory::createUnit(const Point2D& point)
{
    std::shared_ptr<Unit> unit(new Dragon(point));

    return unit;
}
