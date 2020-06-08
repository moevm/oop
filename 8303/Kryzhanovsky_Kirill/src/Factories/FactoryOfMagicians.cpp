//
// Created by therealyou on 05.03.2020.
//

#include "FactoryOfMagicians.h"

Witch *FactoryOfMagicians::createWitch() {
    return new Witch();
}

Elf *FactoryOfMagicians::createElf() {
    return new Elf();
}
