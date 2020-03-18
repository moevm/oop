//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_CREATECOMMAND_H
#define UNTITLED13_CREATECOMMAND_H

#include "../Command.h"
#include "CreateUnitCommand.h"
#include "CreateBaseCommand.h"

class CreateCommandHandler: CommandHandler {

public:

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (cmd.size() < 1){
            std::cout << "Wrong command" << std::endl;
            return CommandPtr(new Command);
        }

        std::string cmdWrd = cmd[0];
        cmd.erase(cmd.begin());
        if (cmdWrd == "unit"){

            return CreateUnitCommandHandler().handle(cmd);

        } else if (cmdWrd == "base"){

            return CreateBaseCommandHandler().handle(cmd);

        }

        return CommandPtr(new Command);

    }

};


#endif //UNTITLED13_CREATECOMMAND_H
