#include "DeathUnitCommand.h"

DeathUnitCommand::DeathUnitCommand(Coordinates d, unsigned hp) : death(d), hpToRestore(hp)
{}

void DeathUnitCommand::exec()
{
    Jesus = (*field)[size_t(death.y)][size_t(death.x)].obj;
    field->delObject(death);
}

void DeathUnitCommand::unExec()
{
    Jesus->heal(hpToRestore);
    (*field)[size_t(death.y)][size_t(death.x)].obj = Jesus;
}
