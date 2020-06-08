//Armor
// Created by therealyou on 11.03.2020.
//

#ifndef LAB1_POISON_H
#define LAB1_POISON_H


#include "Object.h"

class Poison : public Object {
public:
    Poison(int x, int y, int buffValue);
    char getChar() override;
};


#endif //LAB1_POISON_H
