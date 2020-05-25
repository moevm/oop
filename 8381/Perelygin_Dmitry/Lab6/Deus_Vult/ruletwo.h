#ifndef RULETWO_H
#define RULETWO_H
#include "gamerule.h"

class RuleTwo: public GameRule
{
private:
    int UnitCount = 20;
public:
    ~RuleTwo() = default;
    RuleTwo();

    int get_UnitCount() override;
};

#endif // RULETWO_H
