#ifndef DRAGONFACTORY_H
#define DRAGONFACTORY_H

#include "unitfactory.h"

#include "Unit/FlyingUnit/dragon.h"


class DragonFactory : public UnitFactory
{
public:
    explicit DragonFactory() = default;
    virtual ~DragonFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) override;
};

#endif // DRAGONFACTORY_H
