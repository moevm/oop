#ifndef BATTLEFORHONOUR_TENT_H
#define BATTLEFORHONOUR_TENT_H


#include "NeutralObject.h"
#include "../Units/Druid/Hermit.h"
#include "../Units/Druid/Priestess.h"

class Tent: public NeutralObject {

protected:

    void print(std::ostream &stream) const override{
        stream << "TT";
    }

public:

    void toEffect(Unit &unit) override {
        unit.heal(50* strategy->getUnitTypeMultiply());
        if(unit.getUnitType() == UnitType::DRUID) {
            Priestess priestess;
            unit = priestess;
        }
    }

};


#endif //BATTLEFORHONOUR_TENT_H
