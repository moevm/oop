//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_COMMAND_H
#define NEW_LR1_COMMAND_H


#include "../GameField.h"

class Command
{
public:
    virtual void gameCommand() = 0;

protected:
    Command(GameField* Field) : Field(Field) {};
    GameField* Field;
};


#endif //NEW_LR1_COMMAND_H
