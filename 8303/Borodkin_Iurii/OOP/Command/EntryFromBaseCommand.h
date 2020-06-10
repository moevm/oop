#ifndef ENTRYFROMBASECOMMAND_H
#define ENTRYFROMBASECOMMAND_H
#include "Command.h"


class EntryFromBaseCommand : public Command
{
public:
    EntryFromBaseCommand(Object*, Coordinates);
    void exec() override;
    void unExec() override;
private:
    Object* base;
    Unit* unitToRet;
    Coordinates coords;
};

#endif // ENTRYFROMBASECOMMAND_H
