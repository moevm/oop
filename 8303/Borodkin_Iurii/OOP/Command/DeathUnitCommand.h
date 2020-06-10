#ifndef DEATHUNITCOMMAND_H
#define DEATHUNITCOMMAND_H
#include "Command.h"

class DeathUnitCommand : public Command
{
public:
    DeathUnitCommand(Coordinates, unsigned);
    void exec() override;
    void unExec() override;
private:
    Coordinates death;
    Object* Jesus;
    unsigned hpToRestore;
};
#endif // DEATHUNITCOMMAND_H
