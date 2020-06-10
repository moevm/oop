#include "EntryFromBaseCommand.h"

EntryFromBaseCommand::EntryFromBaseCommand(Object* b, Coordinates c) : base(b), coords(c)
{}

void EntryFromBaseCommand::exec()
{
    unitToRet = base->getUnit();
    field->addUnit(unitToRet, coords);
}

void EntryFromBaseCommand::unExec()
{
    base->createUnit(unitToRet);
    (*field).at({coords.y, coords.x}).obj = nullptr;
}
