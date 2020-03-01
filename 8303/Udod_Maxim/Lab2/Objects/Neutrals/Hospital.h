//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_HOSPITAL_H
#define UNTITLED13_HOSPITAL_H


#include "NeutralObject.h"

class Hospital: public NeutralObject {

public:

    void applyTo(Unit &unit) override {

        unit.heal(100*strategy->getUnitTypeFactor());

    }

};


#endif //UNTITLED13_HOSPITAL_H
