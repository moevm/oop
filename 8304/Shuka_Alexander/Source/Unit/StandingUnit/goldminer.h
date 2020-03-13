#ifndef GOLDMINER_H
#define GOLDMINER_H

#include "standingunit.h"


namespace unit {
class GoldMiner : public StandingUnit
{
public:
    explicit GoldMiner(const Point2D& point,
                       std::shared_ptr<Mediator> mediator);

    GoldMiner(const GoldMiner& unit);
    GoldMiner& operator=(const GoldMiner& unit);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;
};
}


#endif // GOLDMINER_H
