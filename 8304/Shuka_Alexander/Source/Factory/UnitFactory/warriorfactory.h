#ifndef WARRIORFACTORY_H
#define WARRIORFACTORY_H

#include "unitfactory.h"

#include "Unit/GroundUnit/warrior.h"


namespace unit {
class WarriorFactory : public UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const override;
};
}

#endif // WARRIORFACTORY_H
