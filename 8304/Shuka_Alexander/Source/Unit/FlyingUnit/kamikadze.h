#ifndef KAMIKADZE_H
#define KAMIKADZE_H

#include "flyingunit.h"


class Kamikadze : public FlyingUnit
{
public:
    explicit Kamikadze(const Point2D& point);
    virtual ~Kamikadze() = default;

    Kamikadze(const Kamikadze& unit);
    Kamikadze(Kamikadze&& unit) = delete;
    Kamikadze& operator=(const Kamikadze& unit);
    Kamikadze& operator=(Kamikadze&& unit) = delete;

    virtual size_t farm() override;

    virtual std::shared_ptr<Unit> clone() override;
};

#endif // KAMIKADZE_H
