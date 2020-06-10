#include "AttackUnitCommand.h"

AttackUnitCommand::AttackUnitCommand(Coordinates a, Coordinates i) : attacking(a), injured(i)
{}

void AttackUnitCommand::exec()
{
    field->attack(attacking, injured);
    hpToRestore = unsigned((*field)[size_t(attacking.y)][size_t(attacking.x)].obj->damage());
}

void AttackUnitCommand::unExec()
{
    (*field)[size_t(injured.y)][size_t(injured.x)].obj->heal(hpToRestore);
}
