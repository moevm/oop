//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_CROSSBOW_H
#define MYGAME_CROSSBOW_H


#include "../Weapon.h"

class Crossbow: public Weapon {
public:
    Crossbow();
    void upgradeWeapon(int *costUpgrade) override;
};


#endif //MYGAME_CROSSBOW_H
