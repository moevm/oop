#ifndef GOGOLEV_STRATEGY_CROSSBOWMAN_HPP
#define GOGOLEV_STRATEGY_CROSSBOWMAN_HPP

#include "../shooter.hpp"

class Crossbowman : public Shooter {
public:
    static const string type;
    Crossbowman();
    int getMaxHP() override;
    int getDamage() override;
    int attackDistance() override;
    int visionDistance() override;
    char getChar(int x, int y) override;
    const string& getType() override;
};



#endif //GOGOLEV_STRATEGY_CROSSBOWMAN_HPP
