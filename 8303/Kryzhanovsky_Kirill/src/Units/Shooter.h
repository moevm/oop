//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_SHOOTER_H
#define LAB1_SHOOTER_H

#include "Alliance.h"

class Shooter : public Alliance {
    char getCharType() const;

public:
    explicit Shooter(int speed=3, int armor=7, int damage=20, int health=280, int rangeAttack=3);
};


#endif //LAB1_SHOOTER_H
