#ifndef DRAGON_H
#define DRAGON_H

#include "flyingunit.h"


class Dragon : public FlyingUnit
{
public:
    explicit Dragon(const Point2D& point);
    virtual ~Dragon() = default;

    Dragon(const Dragon& unit);
    Dragon(Dragon&& unit) = delete;
    Dragon& operator=(const Dragon& unit);
    Dragon& operator=(Dragon&& unit) = delete;

    virtual size_t farm() override;

    virtual std::shared_ptr<Unit> clone() override;
};

#endif // DRAGON_H
