#ifndef GOGOLEV_STRATEGY_ARCHERS_HPP
#define GOGOLEV_STRATEGY_ARCHERS_HPP

#include "../shooter.hpp"

class Archers : public Shooter {
public:
    static const string type;
    Archers();
    int getMaxHP() override;
    int getDamage() override;
    int attackDistance() override;
    int visionDistance() override;
    char getChar(int x, int y) override;
    const string& getType() override;
};


#endif //GOGOLEV_STRATEGY_ARCHERS_HPP
