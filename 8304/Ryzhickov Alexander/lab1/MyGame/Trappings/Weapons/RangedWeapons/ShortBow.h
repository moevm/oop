//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_SHORTBOW_H
#define MYGAME_SHORTBOW_H


#include "../Weapon.h"

class ShortBow: public Weapon {
public:
    ShortBow();
    void upgradeWeapon(int *costUpgrade) override;
};


#endif //MYGAME_SHORTBOW_H
