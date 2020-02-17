#ifndef THIEF_H
#define THIEF_H

#include "groundunit.h"


class Thief : public GroundUnit
{
public:
    explicit Thief(const Point2D& point);
    virtual ~Thief() = default;

    Thief(const Thief& unit);
    Thief(Thief&& unit) = delete;
    Thief& operator=(const Thief& unit);
    Thief& operator=(Thief&& unit) = delete;

    virtual size_t farm() override;

    virtual std::shared_ptr<Unit> clone() override;
};

#endif // THIEF_H
