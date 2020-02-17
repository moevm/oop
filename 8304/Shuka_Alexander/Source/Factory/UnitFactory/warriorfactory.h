#ifndef WARRIORFACTORY_H
#define WARRIORFACTORY_H

#include "unitfactory.h"

#include "Unit/GroundUnit/warrior.h"


class WarriorFactory : public UnitFactory
{
public:
    explicit WarriorFactory() = default;
    virtual ~WarriorFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) override;
};

#endif // WARRIORFACTORY_H
