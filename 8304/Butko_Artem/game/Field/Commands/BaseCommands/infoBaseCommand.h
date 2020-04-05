//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_INFOBASECOMMAND_H
#define NEW_LR1_INFOBASECOMMAND_H
#include "../Command.h"
#include "../../GameField.h"

class infoBaseCommand : public Command
{
public:
    infoBaseCommand(GameField* Field) : Command(Field) {};
    void gameCommand() override;
};


#endif //NEW_LR1_INFOBASECOMMAND_H
