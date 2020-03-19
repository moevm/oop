#include "goldminer.h"

using namespace unit;


GoldMiner::GoldMiner(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    StandingUnit(point, mediator)
{
    healthPoints = 50;
}


size_t GoldMiner::farm() const
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

char GoldMiner::draw() const
{
    return '$';
}
