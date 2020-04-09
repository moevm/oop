//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_GOLDGENERATOR_H
#define MYGAME_GOLDGENERATOR_H


#include "NeutralObject.h"

class GoldGenerator: public NeutralObject  {
private:
    int goldPoints = 50;
    int *addressMoney = nullptr;
public:
    GoldGenerator();
    void operator[](int *something) override ;
    void makeGameMove() override ;
};


#endif //MYGAME_GOLDGENERATOR_H
