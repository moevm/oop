#ifndef GOGOLEV_STRATEGY_SPEARMEN_HPP
#define GOGOLEV_STRATEGY_SPEARMEN_HPP

#include "../infantry.hpp"

class Spearmen : public Infantry {
public:
    static const string type;
    Spearmen();
    int getMaxHP() override;
    DamageType getDamageType() override;
    int getDamage() override;
    char getChar(int x, int y) override;
    const string& getType() override;
};


#endif //GOGOLEV_STRATEGY_SPEARMEN_HPP
