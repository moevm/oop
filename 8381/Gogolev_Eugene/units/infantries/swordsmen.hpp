#ifndef GOGOLEV_STRATEGY_SWORDSMEN_HPP
#define GOGOLEV_STRATEGY_SWORDSMEN_HPP

#include "../infantry.hpp"

class Swordsmen : public Infantry {
public:
    static const string type;
    Swordsmen();
    int getMaxHP() override;
    DamageType getDamageType() override;
    int getDamage() override;
    char getChar(int x, int y) override;
    const string& getType() override;
};



#endif //GOGOLEV_STRATEGY_SWORDSMEN_HPP
