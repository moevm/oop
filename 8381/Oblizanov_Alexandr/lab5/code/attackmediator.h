#ifndef ATTACKMEDIATOR_H
#define ATTACKMEDIATOR_H

#include "base.h"

class AttackMediator : public IAttackMediator
{
public:
    AttackMediator(Field *field);
    void addUnit(IUnit *unit);
    void removeUnit(IUnit *unit);
    bool attack(IUnit *attacker, int deltaX, int deltaY);
    std::vector<IUnit *> getUnits() const;

private:
    std::vector<IUnit *> units;
    Field *field;
};

#endif // ATTACKMEDIATOR_H
