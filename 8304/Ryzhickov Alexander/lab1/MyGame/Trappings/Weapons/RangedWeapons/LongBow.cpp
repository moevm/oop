//
// Created by Alex on 02.03.2020.
//

#include "LongBow.h"

LongBow::LongBow() {
    LongBow::damage = 50;
    LongBow::level = 1;
    LongBow::cost = 250;
    LongBow::bonus = attackBonus::vsAll;
}

void LongBow::upgradeWeapon(int *costUpgrade) {
    if (LongBow::level != 2 && *costUpgrade > LongBow::cost) {
        *costUpgrade = *costUpgrade - LongBow::cost;
        switch (LongBow::level) {
            case 1:
                LongBow::damage += 50;
                LongBow::cost += 250;
                break;
        }
        LongBow::level++;
    }
}
