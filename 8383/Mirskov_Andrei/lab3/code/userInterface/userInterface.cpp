//
// Created by andrei on 29.05.2020.
//

#include "userInterface.h"

UserInterface::UserInterface(Game * game) {
    this->game = game;
}

void printMessage() {
    std::cout << "write <mov x1 y1 x2 y2> to move unit from (x1,y1) to (x2,y2)\n";
    std::cout << "you can only move your units\n";
    std::cout << "write <base x> to check info about x base\n";
}

void UserInterface::run() {
    this->game->printField();
    bool isGameRun = true;
    int baseNum = 1, maxBaseNum = this->game->getBaseCount();
    while (isGameRun) {
        printMessage();
        string command;
        cin >> command;
        if (command == "mov") {
            int x1 = 0,y1 = 0, x2 = 0,y2 = 0;
            std::cin >> x1 >> y1 >> x2 >> y2;
            if (!this->game->moveUnit(x1, y1, x2, y2, baseNum)) {
                std::cout << "Incorrect command\n";
                continue;
            }
        }
        else if (command == "base") {
            int x = 0;
            std::cin >> x;
            this->game->printBaseInfo(x);
            continue;
        }

        this->game->printField();
        baseNum++;
        if (baseNum > maxBaseNum) baseNum = 1;
    }
}
