//
// Created by Глебушунок on 16.03.2020.
//

#ifndef OOP_LAB1_FIELD_H
#define OOP_LAB1_FIELD_H
#include "NeutralObject.h"
#include "NeutralObjectStrategy.h"

class Field: public NeutralObject {


protected:

    void print(std::ostream &stream) const override{

        stream << "F";

    }

public:

    void applyTo(Unit &unit) override {

        unit.heal(10*strategy->getUnitTypeFactor());

    }

};
#endif //OOP_LAB1_FIELD_H
