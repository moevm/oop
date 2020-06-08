//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_TROLL_H
#define LAB1_TROLL_H


#include "Orcs.h"


class Troll : public Orcs {
    char getCharType() const;

public:
    explicit Troll(int speed=5, int armor=8, int damage=13, int health=220, int rangeAttack=2);
};


#endif //LAB1_TROLL_H
