#ifndef OOP1_UNIT_H
#define OOP1_UNIT_H

#include <string>
#include "Condition.h"
#include "SubjectObserve.h"
#include "UnitMediator.h"


class Unit: public SubjectObserve, public UnitMediator{
public:
    Condition condition;
    char name;
    std::string character;
    Unit();
    void death();

    void wasAttack(int damage);
};

#endif //OOP1_UNIT_H
