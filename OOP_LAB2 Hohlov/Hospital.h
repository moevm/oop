//
// Created by Глебушунок on 16.03.2020.
//

#ifndef OOP_LAB1_HOSPITAL_H
#define OOP_LAB1_HOSPITAL_H
#include "NeutralObject.h"

class Hospital: public NeutralObject {


protected:

    void print(std::ostream &stream) const override{

        stream << "HP";

    }

public:

    void applyTo(Unit &unit) override {

        unit.heal(100*strategy->getUnitTypeFactor());

    }

};

#endif //OOP_LAB1_HOSPITAL_H
