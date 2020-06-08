#ifndef BATTLEFORHONOUR_DRUIDSTRATEGY_H
#define BATTLEFORHONOUR_DRUIDSTRATEGY_H


#include "NeutralObjectStrategy.h"

class DruidStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeMultiply() override {
        return 2;
    }

};


#endif //BATTLEFORHONOUR_DRUIDSTRATEGY_H
