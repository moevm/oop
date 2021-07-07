//
// Created by anton on 27.02.2020.
//

#include "Bard.h"
#define BARD_SPECIFICATION {125, 0, 5, 20}

Bard::Bard():Thief(BARD_SPECIFICATION){}

char Bard::getClass() const {
    return 'b';
}