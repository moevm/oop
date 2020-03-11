#include "goldminer.h"


GoldMiner::GoldMiner(const Point2D& point) : StandingUnit(point)
{
    healthPoints = 50;
}


size_t GoldMiner::farm()
{
    return FIVE_GOLD;
}


GoldMiner::GoldMiner(const GoldMiner& unit) : StandingUnit(unit)
{
    this->doCopy(unit);
}


GoldMiner& GoldMiner::operator=(const GoldMiner& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


std::shared_ptr<Unit> GoldMiner::clone()
{
    std::shared_ptr<Unit> unit(new GoldMiner(*this));
    return unit;
}
