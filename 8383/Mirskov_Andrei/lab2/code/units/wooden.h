//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_WOODEN_H
#define OOP_LAB1_WOODEN_H


#include "archer.h"

class WoodenArcher : public Archer {
public:
    WoodenArcher(int x, int y);
    char getType() override;
};


#endif //OOP_LAB1_WOODEN_H
