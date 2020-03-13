#ifndef ARMORUPSTRATEGY_H
#define ARMORUPSTRATEGY_H

#include "Strategy/strategy.h"

#include "Factory/ArmorFactory/heavyarmorfactory.h"
#include "Factory/ArmorFactory/mediumarmorfactory.h"
#include "Factory/ArmorFactory/lightarmorfactory.h"


class ArmorUpStrategy : public Strategy
{
public:
    explicit ArmorUpStrategy() = default;
    virtual ~ArmorUpStrategy() = default;

    ArmorUpStrategy(const ArmorUpStrategy& strategy);
    ArmorUpStrategy(ArmorUpStrategy&& strategy) = delete;
    ArmorUpStrategy& operator=(const ArmorUpStrategy& strategy) = delete;
    ArmorUpStrategy& operator=(ArmorUpStrategy&& strategy) = delete;

    virtual void changeUnit(std::shared_ptr<unit::Unit>& unit) override;

protected:
    std::unique_ptr<Armor> armor;
};

#endif // ARMORUPSTRATEGY_H
