#ifndef KAMIKADZEFACTORY_H
#define KAMIKADZEFACTORY_H

#include "unitfactory.h"

#include "Unit/FlyingUnit/kamikadze.h"


class KamikadzeFactory : public UnitFactory
{
public:
    explicit KamikadzeFactory() = default;
    virtual ~KamikadzeFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) override;
};

#endif // KAMIKADZEFACTORY_H
