//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_ARMORGENERATOR_H
#define MYGAME_ARMORGENERATOR_H


#include "NeutralObject.h"

class ArmorGenerator: public NeutralObject {
private:
    int armorPoints = 50;
public:
    ArmorGenerator();
    void operator[](int *something) override ;
    void makeGameMove() override ;
};


#endif //MYGAME_ARMORGENERATOR_H
