#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "Unit/unit.h"


class UnitFactory
{
public:
    explicit UnitFactory() = default;
    virtual ~UnitFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) = 0;
};

#endif // UNITFACTORY_H
