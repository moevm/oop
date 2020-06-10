#ifndef CreateUnitToBaseCommand_H
#define CreateUnitToBaseCommand_H
#include "Command.h"

class CreateUnitToBaseCommand : public Command
{
public:
    CreateUnitToBaseCommand(Unit*, Coordinates);
    void exec() override;
    void unExec() override;
private:
    Unit* unit;
    Coordinates coords;
};

#endif // CreateUnitToBaseCommand_H
