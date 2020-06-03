#ifndef GOGOLEV_STRATEGY_FARMER_HPP
#define GOGOLEV_STRATEGY_FARMER_HPP

#include "../neutral.hpp"

class Farmer : public Neutral {
public:
    static const string type;
    Farmer();
    int getMaxHP() override;
    DamageType getDamageType() override;
    MovingType getMovingType() override;
    int getDamage() override;
    char getChar (int x, int y) override;
    const string& getType() override;
};


#endif //GOGOLEV_STRATEGY_FARMER_HPP
