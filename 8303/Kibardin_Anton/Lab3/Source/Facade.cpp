//
// Created by anton on 03.04.2020.
//

#include "Facade.h"

void  Facade::startGame() {
    int x, y;
    std::cout << "Let's begin\n" << "Enter field size x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;

    field = new Field(x, y);
    field->printNeutrals();
    field->printLandscape();

    baseHandler = new BaseHandler(field);
    setBaseHandler = new SetBaseHandler(field);
    setUnitHandler = new SetUnitHandler(field);
    moveUnitLeftHandler = new MoveUnitLeftHandler(field);
    moveUnitDownHandler = new MoveUnitDownHandler(field);
    moveUnitUpHandler = new MoveUnitUpHandler(field);
    moveUnitRightHandler = new MoveUnitRightHandler(field);
    attackUnitHandler = new AttackUnitHandler(field);
    showStatusHandler = new ShowStatusHandler(field);
    helpHandler = new HelpHandler(field);

    baseHandler->setNext(setBaseHandler);
    setBaseHandler->setNext(setUnitHandler);
    setUnitHandler->setNext(moveUnitRightHandler);
    moveUnitRightHandler->setNext(moveUnitUpHandler);
    moveUnitUpHandler->setNext(moveUnitDownHandler);
    moveUnitDownHandler->setNext(moveUnitLeftHandler);
    moveUnitLeftHandler->setNext(attackUnitHandler);
    attackUnitHandler->setNext(showStatusHandler);
    showStatusHandler->setNext(helpHandler);

}

void Facade::play() {
    std::string command;
    bool flag = true;
    while(flag)
    {
        std::cout << "enter command: ";
        std::cin >> command;
        baseHandler->handle(command);
    }
}