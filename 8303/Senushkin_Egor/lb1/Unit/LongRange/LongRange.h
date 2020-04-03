//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_LONGRANGE_H
#define OOP_LB1__2_LONGRANGE_H


#include "../../Armor/LightArmor.h"
#include "Archer.h"

class LongRange : public Archer{
public:
    LongRange(){
        armor = LightArmor();
    }

    std::string type() const { return "LongRange"; }
    ~LongRange() = default;
};


#endif //OOP_LB1__2_LONGRANGE_H
