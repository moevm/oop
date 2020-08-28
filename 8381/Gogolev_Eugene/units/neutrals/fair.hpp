#ifndef GOGOLEV_STRATEGY_FAIR_HPP
#define GOGOLEV_STRATEGY_FAIR_HPP

#include "../neutral.hpp"

class Fair : public Neutral {
public:
    static const string type;
    Fair();
    int getMaxHP() override;
    char getChar (int x, int y) override;
    const string& getType() override;
};


#endif //GOGOLEV_STRATEGY_FAIR_HPP
