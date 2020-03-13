#ifndef THIEF_H
#define THIEF_H

#include "groundunit.h"


namespace unit {
class Thief : public GroundUnit
{
public:
    explicit Thief(const Point2D& point,
                   std::shared_ptr<Mediator> mediator);

    Thief(const Thief& unit);
    Thief& operator=(const Thief& unit);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;
};
}

#endif // THIEF_H
