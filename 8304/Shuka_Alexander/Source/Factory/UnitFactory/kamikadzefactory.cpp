#include "kamikadzefactory.h"


std::shared_ptr<Unit> KamikadzeFactory::createUnit(const Point2D& point)
{
    std::shared_ptr<Unit> unit(new Kamikadze(point));

    return unit;
}
