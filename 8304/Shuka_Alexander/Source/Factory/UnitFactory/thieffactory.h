#ifndef THIEFFACTORY_H
#define THIEFFACTORY_H

#include "unitfactory.h"

#include "Unit/GroundUnit/thief.h"


class ThiefFactory : public UnitFactory
{
public:
    explicit ThiefFactory() = default;
    virtual ~ThiefFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Point2D& point) override;
};

#endif // THIEFFACTORY_H
