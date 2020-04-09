//
// Created by Alex on 16.02.2020.
//

#include "Infantry.h"

Infantry::Infantry(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) :  Unit(startX, startY, unitWeapon, unitArmor) {
    setMoves(1);
}

Infantry::Infantry() {

}
