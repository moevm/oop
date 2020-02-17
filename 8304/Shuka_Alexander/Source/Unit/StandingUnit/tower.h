#ifndef TOWER_H
#define TOWER_H

#include "standingunit.h"


class Tower : public StandingUnit
{
public:
    explicit Tower(const Point2D& point);
    virtual ~Tower() = default;

    Tower(const Tower& unit);
    Tower(Tower&& unit) = delete;
    Tower& operator=(const Tower& unit);
    Tower& operator=(Tower&& unit) = delete;

    virtual size_t farm() override;

    virtual std::shared_ptr<Unit> clone() override;
};

#endif // TOWER_H
