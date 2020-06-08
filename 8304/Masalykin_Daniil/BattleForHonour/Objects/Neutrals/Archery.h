#ifndef BATTLEFORHONOUR_ARCHERY_H
#define BATTLEFORHONOUR_ARCHERY_H


#include "NeutralObject.h"
#include "../Units/Archer/CrossBowMan.h"

class Archery: public NeutralObject {

protected:

    void print(std::ostream &stream) const override{
        stream << "AR";
    }

public:

    void toEffect(Unit &unit) override {
        CrossBowMan crossbowman;
        unit = crossbowman;
    }

};


#endif //BATTLEFORHONOUR_ARCHERY_H
