//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_SWORDMAN_H
#define OOP_LAB1_SWORDMAN_H

#include "infantry.h"
#include "../base/base.h"

class Base;

class SwordMan : public Infantry {
public:
    SwordMan(Base *base);

    ~SwordMan();

    char getType() override;

    void notify() override;

    int getBaseNum() override;

private:
    Base* view;
};


#endif //OOP_LAB1_SWORDMAN_H
