#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H
#include "Command.h"
#include <QPushButton>

class AddBaseCommand : public Command
{
public:
    AddBaseCommand(Base*, Coordinates, QPushButton*);

    void exec() override;

    void unExec() override;

private:
    Base* base;
    QPushButton* button;
    Coordinates coords;
};

#endif // ADDOBJECTCOMMAND_H
