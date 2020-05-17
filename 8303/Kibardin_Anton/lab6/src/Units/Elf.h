//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_ELF_H
#define OOP_1_ELF_H


#include "Thief.h"

class Elf: public Thief {

public:
    Elf();

    Elf(Specifications);

    char getClass() const final;
};


#endif //OOP_1_ELF_H
