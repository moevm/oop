//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_WOODEN_H
#define OOP_LAB1_WOODEN_H


#include "archer.h"
#include "../base/base.h"

class Base;

class WoodenArcher : public Archer {
public:
    WoodenArcher(Base *base);

    ~WoodenArcher();

    char getType() override;

    void notify() override;

    int getBaseNum() override;

private:
    Base* view;
};


#endif //OOP_LAB1_WOODEN_H
