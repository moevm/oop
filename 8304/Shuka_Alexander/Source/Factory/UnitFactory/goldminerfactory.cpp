#include "goldminerfactory.h"


std::shared_ptr<Unit> GoldMinerFactory::createUnit(const Point2D& point)
{
    std::shared_ptr<Unit> unit(new GoldMiner(point));

    return unit;
}
