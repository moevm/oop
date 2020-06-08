//
// Created by therealyou on 11.03.2020.
//

#include "Armor.h"

Armor::Armor(int x, int y, int buffValue) :
Object(x, y, buffValue, ObjectsType::ARMOR){

}

char Armor::getChar() {
    return 'A';
}
