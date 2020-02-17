#ifndef STANDINGUNIT_H
#define STANDINGUNIT_H

#include "Unit/unit.h"


class StandingUnit : public Unit
{
public:
    explicit StandingUnit(const Point2D& point);
    virtual ~StandingUnit() = default;

    StandingUnit(const StandingUnit& unit);

    virtual Point2D moveLeft() override;
    virtual Point2D moveRight() override;
    virtual Point2D moveTop() override;
    virtual Point2D moveBottom() override;

    virtual bool isFly() const override;
};

#endif // STANDINGUNIT_H
