#include "MoveUnitCommand.h"

MoveUnitCommand::MoveUnitCommand(Coordinates t, Coordinates f) : to(t), from(f)
{}

void MoveUnitCommand::exec()
{
    (*field).move(to, from);
}

void MoveUnitCommand::unExec()
{
    (*field).move(from, to);
}
