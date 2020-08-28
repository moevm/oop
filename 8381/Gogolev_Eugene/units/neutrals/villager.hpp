#ifndef GOGOLEV_STRATEGY_VILLAGER_HPP
#define GOGOLEV_STRATEGY_VILLAGER_HPP

#include "../neutral.hpp"

class Villager : public Neutral {
public:
    static const string type;
    Villager();
    int getMaxHP() override;
    char getChar (int x, int y) override;
    MovingType getMovingType() override;
    const string& getType() override;
};

#endif //GOGOLEV_STRATEGY_VILLAGER_HPP
