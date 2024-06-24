//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_ARCHERSTRATEGY_H
#define OOP_LAB1_ARCHERSTRATEGY_H

#include "NeutralObjectStrategy.h"

class ArcherStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeFactor() override {
        return 1;
    }

};

#endif //OOP_LAB1_ARCHERSTRATEGY_H
