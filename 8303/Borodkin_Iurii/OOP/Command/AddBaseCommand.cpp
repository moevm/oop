#include "AddBaseCommand.h"

AddBaseCommand::AddBaseCommand(Base* b, Coordinates c, QPushButton* p) : base(b), button(p), coords(c)
{}

void AddBaseCommand::exec()
{
    field->addBase(base, coords);
}

void AddBaseCommand::unExec()
{
    field->delObject(coords);
    button->hide();
}
