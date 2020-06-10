#ifndef MOVEUNITCOMMAND_H
#define MOVEUNITCOMMAND_H
#include "Command.h"

class MoveUnitCommand : public Command
{
public:
    MoveUnitCommand(Coordinates, Coordinates);
    void exec() override;
    void unExec() override;
private:
    Coordinates to;
    Coordinates from;
};
#endif // MOVEUNITCOMMAND_H
