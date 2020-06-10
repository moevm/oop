#ifndef COMMAND_H
#define COMMAND_H
#include "GameField.h"


class Command
{
protected:
    GameField *field;
    int priority = 0;
    Command *next;
public:
    virtual void exec() = 0;
    virtual void unExec() = 0;

    void setField(GameField*);

    virtual ~Command() = default;
};

#endif // COMMAND_H
