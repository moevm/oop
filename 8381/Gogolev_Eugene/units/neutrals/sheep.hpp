#ifndef GOGOLEV_STRATEGY_SHEEP_HPP
#define GOGOLEV_STRATEGY_SHEEP_HPP

#include "../neutral.hpp"

class Sheep : public Neutral {
public:
    static const string type;
    Sheep();
    int getMaxHP() override;
    int getDamage() override;
    DamageType getDamageType() override;
    MovingType getMovingType() override;
    char getChar (int x, int y) override;
    const string& getType() override;
};

#endif //GOGOLEV_STRATEGY_SHEEP_HPP
