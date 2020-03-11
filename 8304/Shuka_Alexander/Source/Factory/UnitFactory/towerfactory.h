#ifndef TOWERFACTORY_H
#define TOWERFACTORY_H

#include "unitfactory.h"

#include "Unit/StandingUnit/tower.h"


class TowerFactory : public UnitFactory
{
public:
    explicit TowerFactory() = default;
    virtual ~TowerFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) override;
};

#endif // TOWERFACTORY_H
