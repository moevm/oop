//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_MOVEUNITCOMMAND_H
#define NEW_LR1_MOVEUNITCOMMAND_H


#include "../Command.h"

class moveUnitCommand : public Command
{
private:
    size_t x1_;
    size_t y1_;
    size_t x2_;
    size_t y2_;
public:
    moveUnitCommand(GameField* Field) : Command(Field) {};
    void gameCommand() override;
};


#endif //NEW_LR1_MOVEUNITCOMMAND_H
