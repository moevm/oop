#ifndef WARRIOR_H
#define WARRIOR_H

#include "groundunit.h"


namespace  unit {
class Warrior : public GroundUnit
{
public:
    explicit Warrior(const Point2D& point,
                     std::shared_ptr<Mediator> mediator);

    Warrior(const Warrior& unit);
    Warrior& operator=(const Warrior& unit);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;
};
}

#endif // WARRIOR_H
