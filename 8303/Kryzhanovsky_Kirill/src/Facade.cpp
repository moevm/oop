//
// Created by therealyou on 06.04.2020.
//

#include "Facade.h"

void Facade::startGame() {
    int x, y;
    std::cout << "Start game" << std::endl
              << "Enter gameField length: ";
    std::cin >> x;
    std::cout << "Enter gameField width: ";
    std::cin >> y;

    adapter = new Adapter();
    gameField = new GameField(x, y, adapter, 1);
    gameField->printFieldNeutralObject();
    gameField->printFieldLandscape();

    baseHandler = new BaseHandler(gameField);
    setBaseHandler = new SetBaseHandler(gameField);
    setUnitHandler = new SetUnitHandler(gameField);
    moveUnitLeftHandler = new MoveUnitLeftHandler(gameField);
    moveUnitDownHandler = new MoveUnitDownHandler(gameField);
    moveUnitUpHandler = new MoveUnitUpHandler(gameField);
    moveUnitRightHandler = new MoveUnitRightHandler(gameField);
    attackUnitHandler = new AttackUnitHandler(gameField);
    showStatusHandler = new ShowStatusHandler(gameField);
    helpHandler = new HelpHandler(gameField);
    adapterHandler = new SwitchLogHandler(adapter);
    turnOnOffLog = new TurnOnOffLog(adapter);
    saveHandler = new SaveHandler(adapter, gameField);
    loadHandler = new LoadHandler(adapter, gameField);

    baseHandler->setNext(setBaseHandler);
    setBaseHandler->setNext(setUnitHandler);
    setUnitHandler->setNext(moveUnitRightHandler);
    moveUnitRightHandler->setNext(moveUnitUpHandler);
    moveUnitUpHandler->setNext(moveUnitDownHandler);
    moveUnitDownHandler->setNext(moveUnitLeftHandler);
    moveUnitLeftHandler->setNext(attackUnitHandler);
    attackUnitHandler->setNext(showStatusHandler);
    showStatusHandler->setNext(helpHandler);
    helpHandler->setNext(adapterHandler);
    adapterHandler->setNext(turnOnOffLog);
    turnOnOffLog->setNext(saveHandler);
    saveHandler->setNext(loadHandler);

}

void Facade::play() {
    std::string command;
    while (true) {
        std::string mode = "";
        std::cout << "enter command: ";
        std::cin >> command;
        if (command == "quit") {
            break;
        }
        baseHandler->handle(command, 1, mode);
    }
}

Facade::Facade() {

}
