//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_SHOWCOMMAND_H
#define UNTITLED13_SHOWCOMMAND_H

#include "../Command.h"
#include "ShowBaseCommand.h"
#include "ShowUnitCommand.h"

class ShowCommandHandler: public CommandHandler{

public:

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (cmd.size() < 1){
            std::cout << "Wrong command" << std::endl;
            return CommandPtr(new Command);
        }

        std::string cmdWrd = cmd[0];
        cmd.erase(cmd.begin());
        if (cmdWrd == "base"){

            return ShowBaseCommandHandler().handle(cmd);

        } else if (cmdWrd == "unit"){

            return ShowUnitCommandHandler().handle(cmd);

        }

        return CommandPtr(new Command);

    }

};

#endif //UNTITLED13_SHOWCOMMAND_H
