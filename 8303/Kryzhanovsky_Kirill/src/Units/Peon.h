//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_PEON_H
#define LAB1_PEON_H

#include "Alliance.h"

class Peon : public Alliance {
    char getCharType() const;
public:
    explicit Peon(int speed=3, int armor=10, int damage=15, int health=210, int rangeAttack=1);

};


#endif //LAB1_PEON_H
