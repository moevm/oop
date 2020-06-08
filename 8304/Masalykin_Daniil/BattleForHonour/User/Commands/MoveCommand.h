#ifndef BATTLEFORHONOUR_MOVECOMMAND_H
#define BATTLEFORHONOUR_MOVECOMMAND_H


#include "Command.h"
#include "MoveUnitCommand.h"

class MoveCommandHandler: public CommandHandler{

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() > 1 && terminal[0] == "move";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){

            terminal.erase(terminal.begin());
            auto handleTemp = new MoveUnitCommandHandler();
            return handleTemp->handle(terminal);

        }
        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};


#endif //BATTLEFORHONOUR_MOVECOMMAND_H
