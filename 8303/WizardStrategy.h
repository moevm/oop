//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_WIZARDSTRATEGY_H
#define OOP_LAB1_WIZARDSTRATEGY_H

#include "NeutralObjectStrategy.h"

class WizardStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeFactor() override {
        return 2;
    }

};

#endif //OOP_LAB1_WIZARDSTRATEGY_H
