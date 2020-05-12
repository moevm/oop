#include <iostream>
#include "Game/Game.h"


int main() {

    Game *game = new Game();

    /*game->gamer1->addArcher(1, 1);
    game->gamer1->addKing(2, 3);
    game->gamer1->addKnight(3, 3);

    game->updateUnitPosition(3,3,1,3);

    game->gamer2->addKnight(7,4);
    game->updateUnitPosition(7,4,9,1);

    game->attackUnit(9,1,1,1);

    game->saveState();*/


    game->loadState();
//    game->gamer2->addSwordsmen(4,4);

    //game->saveState();

//    std::cout << game->checkFile();


    delete game;

    return 0;
}