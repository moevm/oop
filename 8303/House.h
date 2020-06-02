//
// Created by Глебушунок on 16.03.2020.
//

#ifndef OOP_LAB1_HOUSE_H
#define OOP_LAB1_HOUSE_H

#include "NeutralObject.h"

class House: public NeutralObject {

protected:

    void print(std::ostream &stream) const override{

        stream << "HS";

    }

public:

    void applyTo(Unit &unit) override {

        unit.heal(50*strategy->getUnitTypeFactor());

    }

};

#endif //OOP_LAB1_HOUSE_H
