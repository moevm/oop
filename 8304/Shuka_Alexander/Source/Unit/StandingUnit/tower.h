#ifndef TOWER_H
#define TOWER_H

#include "standingunit.h"

namespace unit {
class Tower : public StandingUnit
{
public:
    explicit Tower(const Point2D& point,
                   std::shared_ptr<Mediator> mediator);

    Tower(const Tower& unit);
    Tower& operator=(const Tower& unit);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;
};
}

#endif // TOWER_H
