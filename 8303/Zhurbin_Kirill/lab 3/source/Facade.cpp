#include "Facade.h"

void Facade::createGame() {
    field = new Field(8, 8, 20);
    field->addLandscape();
    field->printLandscape();


    std::cout << "---------------------------"<< std::endl;

    field->addNeutral(1, 1, 'z');
    field->addNeutral(2, 2, 'p');
    field->addNeutral(3, 3, 's');
    field->addNeutral(4, 4, 'a');
    field->printNeutral();
    std::cout << "---------------------------"<< std::endl;

    mediator = new Mediator(field);
    baseHandler = new BaseHandler();
    setBase = new SetBaseHandler(field);
    noCommand = new NoCommandHandler();
    setUnit = new SetUnitHandler(field, mediator);
    moveUnit = new MoveUnitHandler(field);
    statusBase = new StatusBaseHandler(field);
    attackUnit = new AttackUnitHandler(field, mediator);
    baseHandler->add(setBase);
    baseHandler->add(statusBase);
    baseHandler->add(moveUnit);
    baseHandler->add(setUnit);
    baseHandler->add(attackUnit);
    baseHandler->add(noCommand);

    std::cout << "Game preparation done, you can start playing" << std::endl;
}

void Facade::play() {
    std::cout << "Game started" << std::endl;
    std::string commandStr;
    while (true){
        std::cin >> commandStr;
        baseHandler->handle(commandStr);
        field->printAll();
    }
}
