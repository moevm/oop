#ifndef GOGOLEV_STRATEGY_INFANTRY_HPP
#define GOGOLEV_STRATEGY_INFANTRY_HPP

#include "unit.hpp"

class Infantry : public Unit {
public:
    MovingType getMovingType() override;
};

#endif //GOGOLEV_STRATEGY_INFANTRY_HPP
