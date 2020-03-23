//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_ATTACKCOMMAND_H
#define UNTITLED13_ATTACKCOMMAND_H


#include "../Command.h"
#include "AttackUnitCommand.h"

class AttackCommandHandler: CommandHandler {

public:

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (cmd.size() < 1){
            std::cout << "Wrong command" << std::endl;
            return CommandPtr(new Command);
        }

        std::string cmdWrd = cmd[0];
        cmd.erase(cmd.begin());
        if (cmdWrd == "unit"){

            return AttackUnitCommandHandler().handle(cmd);

        }

        return CommandPtr(new Command);

    }

};


#endif //UNTITLED13_ATTACKCOMMAND_H
