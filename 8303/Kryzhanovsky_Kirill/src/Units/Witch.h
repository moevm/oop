//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_WITCH_H
#define LAB1_WITCH_H


#include "Magicians.h"

class Witch : public Magicians {
    char getCharType() const;

public:
    explicit Witch(int speed=4, int armor=3, int damage=25, int health=150, int rangeAttack=4);

};

#endif //LAB1_WITCH_H
