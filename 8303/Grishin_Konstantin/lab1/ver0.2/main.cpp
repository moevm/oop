#include <iostream>

#include "game.h"




int main(){
    auto game = new Game(600, 800);
    game->start();
    delete game;
    return 0;
}
