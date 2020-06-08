#ifndef BATTLEFORHONOUR_NEWCOMMAND_H
#define BATTLEFORHONOUR_NEWCOMMAND_H


#include "Command.h"
#include "NewGameCommand.h"

#include <memory>

class NewCommandHandler: public CommandHandler{

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() > 1 && terminal[0] == "new";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){

            terminal.erase(terminal.begin());
            auto handlerTemp = new NewGameCommandHandler;

            return handlerTemp->handle(terminal);
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();

    }

};



#endif //BATTLEFORHONOUR_NEWCOMMAND_H
