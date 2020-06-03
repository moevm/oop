#ifndef GOGOLEV_STRATEGY_KNIGHT_HPP
#define GOGOLEV_STRATEGY_KNIGHT_HPP

#include "../cavalry.hpp"

class Knight : public Cavalry {
public:
    static const string type;
    Knight();
    int getMaxHP() override;
    DamageType getDamageType() override;
    char getChar(int x, int y) override;
    const string& getType() override;
};

#endif //GOGOLEV_STRATEGY_KNIGHT_HPP
