#include <iostream>
#include "GameFacade.h"

int main() {

    auto unit = new FireMage;

    GameFacade game(2, 6, 6);

    while (!game.isOver()){

        std::cout << game;
        game.nextTurn();

    }

    return 0;
}
