//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_VIKINGSSTRATEGY_H
#define OOP_LAB1_VIKINGSSTRATEGY_H

#include "NeutralObjectStrategy.h"

class VikingsStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeFactor() override {
        return 10;
    }

};


#endif //OOP_LAB1_VIKINGSSTRATEGY_H
