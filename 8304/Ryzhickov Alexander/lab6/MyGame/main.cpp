#include <iostream>
#include "Game/Game.h"

#include "Rules/FirstRule.h"
#include "Rules/SecondRule.h"


int main() {

    /*auto *firstRule = new SecondRule;

    Game *game = new Game(firstRule);

    game->gamer1->addArcher(1, 1);
    game->gamer1->addKing(2, 3);
    game->gamer1->addKnight(3, 3);

    game->updateUnitPosition(3,3,1,3);

    game->gamer2->addKnight(7,4);
    game->updateUnitPosition(7,4,9,1);

    game->attackUnit(9,1,1,1);

    game->saveState();


//    game->loadState();
//    game->gamer2->addSwordsmen(4,4);

    //game->saveState();

//    std::cout << game->checkFile();


    delete game;
    delete firstRule;*/


    Game &game = Game::Instance();

    game.getCurrentGamer()->addArcher(1,1);
    game.getCurrentGamer()->addKing(2, 3);
    game.getCurrentGamer()->addKnight(3, 3);

    game.updateUnitPosition(3, 3, 1, 3);

    game.switchOrder();
    game.getCurrentGamer()->addKing(7, 4);

    game.updateUnitPosition(7,4,1,1);

    //game->updateUnitPosition(7, 4, 9, 1);

    //game->attackUnit(9, 1, 2, 3);



    game.saveState();
//    game->startNewGame();
//    game->saveState();


//    delete game;
//    delete firstRule;

    return 0;
}