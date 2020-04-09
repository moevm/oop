//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_HEALTHGENERATOR_H
#define MYGAME_HEALTHGENERATOR_H


#include "NeutralObject.h"

class HealthGenerator: public NeutralObject  {
private:
    int healthPoints = 50;
public:
    HealthGenerator();
    void operator[](int *something) override ;
    void makeGameMove() override ;
};


#endif //MYGAME_HEALTHGENERATOR_H
