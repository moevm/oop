//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_CREATEUNITCOMMAND_H
#define NEW_LR1_CREATEUNITCOMMAND_H


#include "../Command.h"

class createUnitCommand : public Command
{
private:
    char id_;
public:
    createUnitCommand(GameField* Field) : Command(Field) {};
    void gameCommand() override;
};


#endif //NEW_LR1_CREATEUNITCOMMAND_H
