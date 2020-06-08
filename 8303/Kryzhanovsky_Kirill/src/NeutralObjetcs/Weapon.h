//
// Created by therealyou on 11.03.2020.
//

#ifndef LAB1_WEAPON_H
#define LAB1_WEAPON_H


#include "Object.h"

class Weapon : public Object {
public:
    Weapon(int x, int y, int buffValue);
    char getChar() override;
};


#endif //LAB1_WEAPON_H
