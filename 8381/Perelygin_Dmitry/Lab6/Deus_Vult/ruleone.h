#ifndef RULEONE_H
#define RULEONE_H
#include "gamerule.h"

class Ruleone: public GameRule
{
private:
    int UnitCount = 10;
public:
    ~Ruleone() = default;
    Ruleone();

    int get_UnitCount() override;
};

#endif // RULEONE_H
