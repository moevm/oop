//
// Created by Artem Butko on 04/04/2020.
//

#include "Facade.h"

void Facade::createGame()
{
    Field = new GameField(5,5);
    Field->printField();

    gameCommand = new CoR();

    gameCommand->addNext(new CreateBaseCOR(Field));
    gameCommand->addNext(new InfoBaseCOR(Field));
    gameCommand->addNext(new CreateUnitCOR(Field));
    gameCommand->addNext(new GetUnitCOR(Field));
    gameCommand->addNext(new UnknownCOR(Field));


}

void Facade::playGame()
{
    std::string CommandID;
    while(true)
    {
        std::cin >> CommandID;
        if (CommandID == "EXIT") break;
        gameCommand->chain(CommandID);
        Field->printField();
        std::cout << std::endl;
    }
}
