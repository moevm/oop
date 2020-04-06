#include "UnitMediators.h"

#include <utility>

#include "../Units/Unit.h"
#include "GameField/GameField.h"

UnitMediator::UnitMediator(std::shared_ptr<IGameField> field_, std::shared_ptr<Unit> unit_) :
    field(std::move(field_)), unit(std::move(unit_))
{ }

/*      MOVE MEDIATOR       */

UnitMoveMediator::UnitMoveMediator(std::shared_ptr<IGameField> field_, std::shared_ptr<Unit> unit_) :
    UnitMediator(std::move(field_), std::move(unit_))
{ }

void UnitMoveMediator::Notify(std::shared_ptr<Unit> sender, size_t x, size_t y)
{
    field->moveUnit(sender, x, y);
}

void UnitMoveMediator::connectWithUnit()
{
    unit->setUnitMoveMediator(shared_from_this());
}

/*      ATTACK MEDIATOR       */

UnitMeleeAttackMediator::UnitMeleeAttackMediator(std::shared_ptr<IGameField> field_, std::shared_ptr<Unit> unit_) :
        UnitMediator(std::move(field_), std::move(unit_))
{ }

void UnitMeleeAttackMediator::connectWithUnit()
{
    unit->setUnitMeleeAttackMediator(shared_from_this());
}

void UnitMeleeAttackMediator::Notify(std::shared_ptr<Unit> sender, size_t x, size_t y)
{
    field->meleeAttackUnit(sender, x, y);
}
