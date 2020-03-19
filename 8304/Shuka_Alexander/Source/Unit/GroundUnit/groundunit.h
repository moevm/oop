#ifndef GROUNDUNIT_H
#define GROUNDUNIT_H

#include "Unit/unit.h"


namespace unit {
class GroundUnit : public Unit,
        public std::enable_shared_from_this<Unit>
{
public:
    explicit GroundUnit(const Point2D& point,
                        std::shared_ptr<Mediator> mediator);

    GroundUnit(const GroundUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;

    virtual bool isFly() const override;
};
}

#endif // GROUNDUNIT_H
