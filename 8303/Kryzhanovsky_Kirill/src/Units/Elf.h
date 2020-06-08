//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_ELF_H
#define LAB1_ELF_H


#include "Magicians.h"

class Elf : public Magicians {
    char getCharType() const;

public:
    explicit Elf(int speed=3, int armor=5, int damage=18, int health=180, int rangeAttack=3);
};


#endif //LAB1_ELF_H
