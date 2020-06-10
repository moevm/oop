#include "CreateUnitToBaseCommand.h"

CreateUnitToBaseCommand::CreateUnitToBaseCommand(Unit* u, Coordinates c) : unit(u), coords(c)
{}

void CreateUnitToBaseCommand::exec()
{
    (*field).addUnit(unit, coords);
}

void CreateUnitToBaseCommand::unExec()
{
    delete field->at({coords.y, coords.x}).obj->getUnit();
}
