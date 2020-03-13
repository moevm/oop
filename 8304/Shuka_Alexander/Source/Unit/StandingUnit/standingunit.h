#ifndef STANDINGUNIT_H
#define STANDINGUNIT_H

#include "Unit/unit.h"


namespace unit {
class StandingUnit : public Unit,
        public std::enable_shared_from_this<Unit>
{
public:
    explicit StandingUnit(const Point2D& point,
                          std::shared_ptr<Mediator> mediator);

    StandingUnit(const StandingUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;

    virtual bool isFly() const override;
};
}

#endif // STANDINGUNIT_H
