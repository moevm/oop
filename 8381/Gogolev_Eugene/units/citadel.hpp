#ifndef GOGOLEV_STRATEGY_CITADEL_HPP
#define GOGOLEV_STRATEGY_CITADEL_HPP

#include "unit.hpp"

class Citadel : public Unit {
public:
    static const string type;
    Citadel();
    int getMaxHP() override;
    char getChar(int x, int y) override;
    void update() override;

    void save(ostream &os);
    void load(istream &is);
    const string& getType();

private:
    int unitCap = 5;
    int unitTypeIndex = 0;
    vector<int> unitList;

    Unit* createUnit();
};


#endif //GOGOLEV_STRATEGY_CITADEL_HPP
