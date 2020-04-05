//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_GETUNITCOMMAND_H
#define NEW_LR1_GETUNITCOMMAND_H


#include "../Command.h"

class getUnitCommand : public Command
{
private:
    size_t x_;
    size_t y_;
    size_t quantity_;
    char id_;
public:
    getUnitCommand(GameField* Field) : Command(Field) {};
    void gameCommand() override;
};


#endif //NEW_LR1_GETUNITCOMMAND_H
