//
// Created by Alex on 02.03.2020.
//

#include "ShortBow.h"

ShortBow::ShortBow() {
    ShortBow::damage = 25;
    ShortBow::level = 1;
    ShortBow::cost = 30;
    ShortBow::bonus = attackBonus::vsInfantry;
}

void ShortBow::upgradeWeapon(int *costUpgrade) {
    if (ShortBow::level != 3 && *costUpgrade > ShortBow::cost) {
        switch (ShortBow::level) {
            case 1:
                ShortBow::damage += 10;
                ShortBow::cost += 25;
                break;
            case 2:
                ShortBow::damage += 10;
                ShortBow::cost += 25;
                break;
        }
        ShortBow::level++;
    }
}
