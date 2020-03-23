//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_SWORDMAN_H
#define OOP_LAB1_SWORDMAN_H

#include "infantry.h"

class SwordMan : public Infantry {
public:
    SwordMan(int x, int y);
    char getType() override;
};


#endif //OOP_LAB1_SWORDMAN_H
