#ifndef DESTROYBASECOMMAND_H
#define DESTROYBASECOMMAND_H
#include "Command.h"
#include <vector>

class DestroyBaseCommand : public Command
{
public:
    DestroyBaseCommand(Coordinates, unsigned, std::vector<Object**>);
    void exec() override;
    void unExec() override;
private:
    Coordinates destroyed;
    Object* saveBase;
    unsigned hpToRestore;
    std::vector <Object**> clones;
};

#endif // DESTROYBASECOMMAND_H
