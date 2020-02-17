#ifndef UNIT_H
#define UNIT_H
#include <string>
#include "Object.h"

class Unit : public Object
{
public:
    enum Healths {
        H_ARCHER = 250 , H_WIZARD    = 375 ,
        H_PANZER = 1250, H_SWORDSMAN = 1000,
        H_CENTAUR  = 600 , H_SPEARMAN  = 350
    };
    enum Attacks {
        ATT_ARCHER = 50, ATT_WIZARD    = 150,
        ATT_PANZER = 50, ATT_SWORDSMAN = 100,
        ATT_CENTAUR  = 25, ATT_SPEARMAN  = 75
    };
protected:
    unsigned _attack;
    explicit Unit(std::pair<int, int>, std::string = "");
    std::string type() const override;
};

#endif // UNIT_H
