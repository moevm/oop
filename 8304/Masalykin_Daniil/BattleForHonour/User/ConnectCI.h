#ifndef BATTLEFORHONOUR_CONNECTCI_H
#define BATTLEFORHONOUR_CONNECTCI_H


#include "Commands/Command.h"

#include "Commands/AttackCommand.h"
#include "Commands/CreateCommand.h"
#include "Commands/MoveCommand.h"
#include "Commands/ShowCommand.h"
#include "Commands/ExitCommand.h"
#include "Commands/NewCommand.h"

class ConnectCI {

private:

    AttackCommandHandler *attackHandler;
    CreateCommandHandler *createHandler;
    MoveCommandHandler *moveHandler;
    ShowCommandHandler *showHandler;
    ExitCommandHandler *exitHandler;
    NewCommandHandler *newHandler;

public:

    ConnectCI(){

        newHandler = new NewCommandHandler();
        attackHandler = new AttackCommandHandler();
        createHandler = new CreateCommandHandler();
        moveHandler = new MoveCommandHandler();
        showHandler = new ShowCommandHandler();
        exitHandler = new ExitCommandHandler();


        attackHandler->setNext(createHandler);
        createHandler->setNext(moveHandler);
        moveHandler->setNext(showHandler);
        showHandler->setNext(exitHandler);
        exitHandler->setNext(newHandler);
    }

    std::unique_ptr<Command> handle(std::string commandString){

        std::vector <std::string> splitCommands;
        std::stringstream stream(commandString);
        std::string commandWord;
        while (stream >> commandWord)
            splitCommands.push_back(commandWord);

        return attackHandler->handle(splitCommands);

    }

    ~ConnectCI(){
        delete attackHandler;
        delete createHandler;
        delete moveHandler;
        delete showHandler;
        delete exitHandler;
    }


};


#endif //BATTLEFORHONOUR_CONNECTCI_H
