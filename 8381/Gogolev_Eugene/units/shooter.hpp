#ifndef GOGOLEV_STRATEGY_SHOOTER_HPP
#define GOGOLEV_STRATEGY_SHOOTER_HPP

#include "unit.hpp"

class Shooter : public Unit {
public:
    MovingType getMovingType() override;
    DamageType getDamageType() override;

    //TODO перезарядка
};


#endif //GOGOLEV_STRATEGY_SHOOTER_HPP
