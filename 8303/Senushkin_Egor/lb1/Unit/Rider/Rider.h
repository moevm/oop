//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_RIDER_H
#define OOP_LB1__2_RIDER_H

#include "../Unit.h"
#include "../../Armor/HeavyArmor .h"

class Rider : public Unit {

protected:
    Rider() {
        armor = HeavyArmor();
    }

public:
    std::string type() const { return "Rider"; }
    ~Rider() = default;
};

#endif //OOP_LB1__2_RIDER_H
