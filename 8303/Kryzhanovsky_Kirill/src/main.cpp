#include <iostream>
#include "Game.h"

Game<Rule1, 2> *Game<Rule1, 2>::game = nullptr;
Game<Rule2, 2> *Game<Rule2, 2>::game = nullptr;
Game<Rule1, 3> *Game<Rule1, 3>::game = nullptr;
Game<Rule2, 3> *Game<Rule2, 3>::game = nullptr;

int main() {
    std::string modeGame;
    int countPlayers;

    std::cout << "Let's begin" << std::endl;
    std::cout << "choose game mode(baseDefence/titans): ";
    std::cin >> modeGame;
    while (modeGame != "baseDefence" && modeGame != "titans") {
        std::cout << "Mode game can be baseDefence or titans: ";
        std::cin >> modeGame;
    }

    std::cout << "Enter count of players(2/3): ";
    std::cin >> countPlayers;

    while (countPlayers != 2 && countPlayers != 3) {
        std::cout << "Count of players can be 2 or 3: ";
        std::cin >> countPlayers;
    }

    if (modeGame == "baseDefence") {
        if (countPlayers == 2) {
            auto *game = Game<Rule1, 2>::getInstance();
            game->createGame();
            game->play();

        } else {
            auto *game = Game<Rule1, 3>::getInstance();
            game->createGame();
            game->play();
        }
    } else {
        if (countPlayers == 2) {
            auto *game = Game<Rule2, 2>::getInstance();
            game->createGame();
            game->play();
        } else {
            auto *game = Game<Rule2, 3>::getInstance();
            game->createGame();
            game->play();
        }
    }
    return 0;
}