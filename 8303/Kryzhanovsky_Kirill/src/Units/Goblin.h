//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_GOBLIN_H
#define LAB1_GOBLIN_H


#include "Orcs.h"

class Goblin : public Orcs {
    char getCharType() const;

public:
    explicit Goblin(int speed=4, int armor=12, int damage=16, int health=190, int rangeAttack=1);
};


#endif //LAB1_GOBLIN_H
