#ifndef BATTLEFORHONOUR_ARCHERSTRATEGY_H
#define BATTLEFORHONOUR_ARCHERSTRATEGY_H


#include "NeutralObjectStrategy.h"

class ArcherStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeMultiply() override {
        return 1;
    }
};


#endif //BATTLEFORHONOUR_ARCHERSTRATEGY_H
