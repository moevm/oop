#include <iostream>
#include "Game/Game.h"

#include "Rules/FirstRule.h"
#include "Rules/SecondRule.h"

using namespace MyGame;

int main() {


    Game &game = Game::Instance();

    game.getCurrentGamer()->addArcher(1,1);
    game.getCurrentGamer()->addKing(2, 3);
    game.getCurrentGamer()->addKnight(3, 3);
//    game.getCurrentGamer()->addSwordsmen(3,3);

    game.updateUnitPosition(3, 3, 3, 1);

    game.switchOrder();
    game.getCurrentGamer()->addKing(7, 4);

    game.updateUnitPosition(7,4,1,2);

    game.attackUnit(1,1,1,2);

    game.startNewGame();

    return 0;
}