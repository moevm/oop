//
// Created by andrei on 29.05.2020.
//

#ifndef OOP_LAB2_USERINTERFACE_H
#define OOP_LAB2_USERINTERFACE_H

#include <iostream>
#include "../game/game.h"


class UserInterface {
public:
    UserInterface(Game*);
    void run();
private:
    Game* game;
};


#endif //OOP_LAB2_USERINTERFACE_H
