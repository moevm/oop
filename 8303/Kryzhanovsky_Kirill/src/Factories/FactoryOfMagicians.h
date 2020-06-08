//
// Created by therealyou on 05.03.2020.
//

#ifndef LAB1_FACTORYOFMAGICIANS_H
#define LAB1_FACTORYOFMAGICIANS_H


#include "FactoryOfUnits.h"
#include "../Units/Elf.h"
#include "../Units/Witch.h"

class FactoryOfMagicians : public FactoryOfUnits{
public:
    Elf* createElf();
    Witch* createWitch();
};


#endif //LAB1_FACTORYOFMAGICIANS_H
