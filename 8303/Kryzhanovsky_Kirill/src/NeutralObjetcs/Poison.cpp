//
// Created by therealyou on 11.03.2020.
//

#include "Poison.h"

Poison::Poison(int x, int y, int buffValue) :
Object(x, y, buffValue, ObjectsType::POISON) {

}

char Poison::getChar() {
    return 'P';
}
