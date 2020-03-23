//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_FIREARCHER_H
#define OOP_LAB1_FIREARCHER_H

#include "archer.h"

class FireArcher : public Archer {
public:
    FireArcher(int x, int y);
    char getType() override;
};


#endif //OOP_LAB1_FIREARCHER_H
