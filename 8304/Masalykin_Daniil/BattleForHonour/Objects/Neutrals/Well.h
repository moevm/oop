#ifndef BATTLEFORHONOUR_WELL_H
#define BATTLEFORHONOUR_WELL_H


#include "NeutralObject.h"
#include "NeutralObjectStrategy.h"

class Well: public NeutralObject {

protected:
    void print(std::ostream &stream) const override{
        stream << "WL";
    }

public:

    void toEffect(Unit &unit) override {
        unit.heal(10* strategy->getUnitTypeMultiply());
        if(unit.getUnitType() == UnitType::ARCHER) {
            unit.getWeapon() = StarFall();
        }
    }

};


#endif //BATTLEFORHONOUR_WELL_H
