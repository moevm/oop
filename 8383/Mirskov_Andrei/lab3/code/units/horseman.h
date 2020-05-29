//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_HORSEMAN_H
#define OOP_LAB1_HORSEMAN_H


#include "rider.h"
#include "../base/base.h"

class Base;

class HorseMan : public Rider {
public:
    HorseMan(Base *base);

    ~HorseMan();

    char getType() override;

    void notify() override;

    int getBaseNum() override;

private:
    Base* view;
};


#endif //OOP_LAB1_HORSEMAN_H
