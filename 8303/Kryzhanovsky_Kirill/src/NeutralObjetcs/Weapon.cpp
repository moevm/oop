//
// Created by therealyou on 11.03.2020.
//

#include "Weapon.h"

Weapon::Weapon(int x, int y, int buffValue) :
Object(x, y, buffValue, ObjectsType::WEAPON) {

}

char Weapon::getChar() {
    return 'W';
}
