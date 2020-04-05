//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_NONECOMMAND_H
#define NEW_LR1_NONECOMMAND_H

#include "../Command.h"

class noneCommand : public Command
{
public:
    noneCommand() : Command(nullptr) {};
    void gameCommand();
};


#endif //NEW_LR1_NONECOMMAND_H
