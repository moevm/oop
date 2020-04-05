//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_CREATEBASECOMMAND_H
#define NEW_LR1_CREATEBASECOMMAND_H

#include "../Command.h"
#include "../../GameField.h"

class createBaseCommand : public Command
{
private:
    size_t x;
    size_t y;
    int limit;
public:
    createBaseCommand(GameField* Field) : Command(Field) {};
    void gameCommand() override;
};


#endif //NEW_LR1_CREATEBASECOMMAND_H
