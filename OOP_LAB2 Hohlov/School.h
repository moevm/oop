//
// Created by Глебушунок on 16.03.2020.
//

#ifndef OOP_LAB1_SCHOOL_H
#define OOP_LAB1_SCHOOL_H

#include "NeutralObject.h"
#include "FireMage.h"

class Hogwarts: public NeutralObject {


protected:

    void print(std::ostream &stream) const override{

        stream << "SCH";

    }

public:

    void applyTo(Unit &unit) override {

        FireMage mage;
        unit = mage;

    }

};


#endif //OOP_LAB1_SCHOOL_H
