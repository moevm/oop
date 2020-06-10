#ifndef ATTACKUNITCOMMAND_H
#define ATTACKUNITCOMMAND_H
#include "Command.h"

class AttackUnitCommand : public Command
{
public:
    AttackUnitCommand(Coordinates, Coordinates);
    void exec() override;
    void unExec() override;
private:
    Coordinates attacking;
    Coordinates injured;
    unsigned hpToRestore;
};
#endif // ATTACKUNITCOMMAND_H
