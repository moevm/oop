//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_HORSEMAN_H
#define OOP_LAB1_HORSEMAN_H


#include "rider.h"

class HorseMan : public Rider {
public:
    HorseMan(int x, int y);
    char getType() override;
};


#endif //OOP_LAB1_HORSEMAN_H
