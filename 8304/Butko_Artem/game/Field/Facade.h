//
// Created by Artem Butko on 04/04/2020.
//

#ifndef NEW_LR1_FACADE_H
#define NEW_LR1_FACADE_H

#include "GameField.h"
#include "CoR.h"

class Facade
{
public:
    void createGame();
    void playGame();
private:
    GameField *Field;
    CoR *gameCommand;
};


#endif //NEW_LR1_FACADE_H
