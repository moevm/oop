#ifndef WARRIOR_H
#define WARRIOR_H

#include "groundunit.h"


class Warrior : public GroundUnit
{
public:
    explicit Warrior(const Point2D& point);
    virtual ~Warrior() = default;

    Warrior(const Warrior& unit);
    Warrior(Warrior&& unit) = delete;
    Warrior& operator=(const Warrior& unit);
    Warrior& operator=(Warrior&& unit) = delete;

    virtual size_t farm() override;

    virtual std::shared_ptr<Unit> clone() override;
};

#endif // WARRIOR_H
