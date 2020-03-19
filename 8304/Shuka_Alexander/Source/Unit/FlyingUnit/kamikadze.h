#ifndef KAMIKADZE_H
#define KAMIKADZE_H

#include "flyingunit.h"


namespace unit {
class Kamikadze : public FlyingUnit
{
public:
    explicit Kamikadze(const Point2D& point,
                       std::shared_ptr<Mediator> mediator);

    Kamikadze(const Kamikadze& unit);
    Kamikadze& operator=(const Kamikadze& unit);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;
};
}

#endif // KAMIKADZE_H
