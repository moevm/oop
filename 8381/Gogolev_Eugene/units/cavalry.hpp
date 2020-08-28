#ifndef GOGOLEV_STRATEGY_CAVALRY_HPP
#define GOGOLEV_STRATEGY_CAVALRY_HPP

#include "unit.hpp"

class Cavalry : public Unit {
public:
    int getSpeed() override;
    MovingType getMovingType() override;
    void takeDamage(DamageType damageType, int value) override;
};


#endif //GOGOLEV_STRATEGY_CAVALRY_HPP
