#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "Unit/unit.h"


namespace unit {
class UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const = 0;
};
}

#endif // UNITFACTORY_H
