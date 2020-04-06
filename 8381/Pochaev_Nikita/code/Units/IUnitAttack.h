#ifndef OOP_IUNITATTACK_H
#define OOP_IUNITATTACK_H

#include "AuxiliaryFunctionality/UnitMediators.h"

class IUnitAttack
{
public:
    virtual ~IUnitAttack() = default;
    virtual void setUnitMeleeAttackMediator(std::shared_ptr<UnitMeleeAttackMediator> mediator_) = 0;
    virtual void carryOutMeleeAttack(size_t x, size_t y) = 0;

protected:
    std::shared_ptr<UnitMeleeAttackMediator> meleeAttackMediator;
};

#endif //OOP_IUNITATTACK_H
