#ifndef GOGOLEV_STRATEGY_NEUTRAL_HPP
#define GOGOLEV_STRATEGY_NEUTRAL_HPP

#include "unit.hpp"

class Neutral : public Unit {
public:
    void spotted(Unit* other) override;
};


#endif //GOGOLEV_STRATEGY_NEUTRAL_HPP
