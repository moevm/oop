#ifndef GOLDMINER_H
#define GOLDMINER_H

#include "standingunit.h"


class GoldMiner : public StandingUnit
{
public:
    explicit GoldMiner(const Point2D& point);
    virtual ~GoldMiner() = default;

    GoldMiner(const GoldMiner& unit);
    GoldMiner(GoldMiner&& unit) = delete;
    GoldMiner& operator=(const GoldMiner& unit);
    GoldMiner& operator=(GoldMiner&& unit) = delete;

    virtual size_t farm() override;

    virtual std::shared_ptr<Unit> clone() override;
};


#endif // GOLDMINER_H
