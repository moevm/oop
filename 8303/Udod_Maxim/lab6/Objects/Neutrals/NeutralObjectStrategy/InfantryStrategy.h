//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_INFANTRYSTRATEGY_H
#define UNTITLED13_INFANTRYSTRATEGY_H


#include "NeutralObjectStrategy.h"

class InfantryStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeFactor() override {
        return 10;
    }

};


#endif //UNTITLED13_INFANTRYSTRATEGY_H
