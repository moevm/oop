#ifndef GOLDMINERFACTORY_H
#define GOLDMINERFACTORY_H

#include "unitfactory.h"

#include "Unit/StandingUnit/goldminer.h"


class GoldMinerFactory : public UnitFactory
{
public:
    explicit GoldMinerFactory() = default;
    virtual ~GoldMinerFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) override;
};

#endif // GOLDMINERFACTORY_H
