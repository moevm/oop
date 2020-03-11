#ifndef GROUNDUNIT_H
#define GROUNDUNIT_H

#include "Unit/unit.h"


class GroundUnit : public Unit
{
public:
    explicit GroundUnit(const Point2D& point);
    virtual ~GroundUnit() = default;

    GroundUnit(const GroundUnit& unit);

    virtual Point2D moveLeft() override;
    virtual Point2D moveRight() override;
    virtual Point2D moveTop() override;
    virtual Point2D moveBottom() override;

    virtual bool isFly() const override;
};

#endif // GROUNDUNIT_H
