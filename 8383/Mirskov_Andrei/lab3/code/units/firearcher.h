//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_FIREARCHER_H
#define OOP_LAB1_FIREARCHER_H

#include "archer.h"
#include "../base/base.h"

class Base;

class FireArcher : public Archer {
public:
    FireArcher(Base *base);

    ~FireArcher();

    char getType() override;

    void notify() override;

    int getBaseNum() override;

private:
    Base* view;
};


#endif //OOP_LAB1_FIREARCHER_H
