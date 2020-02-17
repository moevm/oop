#ifndef FLYINGUNIT_H
#define FLYINGUNIT_H

#include "Unit/unit.h"


class FlyingUnit : public Unit
{
public:
    explicit FlyingUnit(const Point2D& point);
    virtual ~FlyingUnit() = default;

    FlyingUnit(const FlyingUnit& unit);

    virtual Point2D moveLeft() override;
    virtual Point2D moveRight() override;
    virtual Point2D moveTop() override;
    virtual Point2D moveBottom() override;

    virtual bool isFly() const override;
};

#endif // FLYINGUNIT_H
