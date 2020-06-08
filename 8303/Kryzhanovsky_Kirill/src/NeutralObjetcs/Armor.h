//
// Created by therealyou on 11.03.2020.
//

#ifndef LAB1_ARMOR_H
#define LAB1_ARMOR_H


#include "Object.h"

class Armor : public Object {
public:
    Armor(int x, int y, int buffValue);

    char getChar() override;
};


#endif //LAB1_ARMOR_H
