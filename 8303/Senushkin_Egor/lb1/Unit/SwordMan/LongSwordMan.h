//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_LONGSWORDMAN_H
#define OOP_LB1__2_LONGSWORDMAN_H

#include "SwordMan.h"
#include "../../Weapon/LongSword.h"

class LongSwordMan : public SwordMan{
public:
    LongSwordMan()
    {
        weapon = LongSword();
        health = 150;
    }
    std::string type() const { return "LongSwordMan"; }
    ~LongSwordMan() = default;

};

#endif //OOP_LB1__2_LONGSWORDMAN_H
