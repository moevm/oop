//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_LONGBOW_H
#define MYGAME_LONGBOW_H


#include "../Weapon.h"

class LongBow: public Weapon{
public:
    LongBow();
    void upgradeWeapon(int *costUpgrade) override;
};


#endif //MYGAME_LONGBOW_H
