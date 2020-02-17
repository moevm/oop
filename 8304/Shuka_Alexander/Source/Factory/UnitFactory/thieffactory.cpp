#include "thieffactory.h"


std::shared_ptr<Unit> ThiefFactory::createUnit(const Point2D& point)
{
    std::shared_ptr<Unit> unit(new Thief(point));

    return unit;
}
