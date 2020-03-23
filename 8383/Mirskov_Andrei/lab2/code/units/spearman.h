//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_SPEARMAN_H
#define OOP_LAB1_SPEARMAN_H

#include "infantry.h"

class SpearMan : public Infantry {
public:
    SpearMan(int x, int y);
    char getType() override ;
};


#endif //OOP_LAB1_SPEARMAN_H
