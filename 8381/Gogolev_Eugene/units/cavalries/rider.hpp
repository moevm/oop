#ifndef GOGOLEV_STRATEGY_RIDER_HPP
#define GOGOLEV_STRATEGY_RIDER_HPP

#include "../cavalry.hpp"

class Rider : public Cavalry {
public:
    static const string type;
    Rider();
    int getMaxHP() override;
    DamageType getDamageType() override;
    char getChar(int x, int y) override;
    const string& getType() override;
};

#endif //GOGOLEV_STRATEGY_RIDER_HPP
