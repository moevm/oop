#ifndef BATTLEFORHONOUR_LOADCI_H
#define BATTLEFORHONOUR_LOADCI_H


#include "Commands/Command.h"
#include "Commands/AttackCommand.h"
#include "Commands/CreateCommand.h"
#include "Commands/MoveCommand.h"
#include "Commands/ShowCommand.h"
#include "Commands/ExitCommand.h"
#include "Commands/NewCommand.h"
#include "Commands/SkipCommand.h"

class LoadCI {

private:

    AttackCommandHandler *attackHandler;
    CreateCommandHandler *createHandler;
    MoveCommandHandler *moveHandler;
    ShowCommandHandler *showHandler;
    ExitCommandHandler *exitHandler;
    NewCommandHandler *newHandler;
    SkipCommandHandler *skipHandler;


public:

    LoadCI(){
        newHandler = new NewCommandHandler();
        attackHandler = new AttackCommandHandler();
        createHandler = new CreateCommandHandler();
        moveHandler = new MoveCommandHandler();
        showHandler = new ShowCommandHandler();
        exitHandler = new ExitCommandHandler();
        skipHandler = new SkipCommandHandler();

        attackHandler->setNext(createHandler);
        createHandler->setNext(moveHandler);
        moveHandler->setNext(showHandler);
        showHandler->setNext(exitHandler);
        exitHandler->setNext(newHandler);
        newHandler->setNext(skipHandler);
    }

    std::unique_ptr<Command> handle(std::string commandString){

        std::vector <std::string> splitCommands;
        std::stringstream stream(commandString);
        std::string commandWord;
        while (stream >> commandWord)
            splitCommands.push_back(commandWord);

        return attackHandler->handle(splitCommands);

    }

    ~LoadCI(){
        delete attackHandler;
        delete createHandler;
        delete moveHandler;
        delete showHandler;
        delete exitHandler;
        delete skipHandler;
    }


};


#endif //BATTLEFORHONOUR_LOADCI_H
