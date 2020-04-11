//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_ELEPHANTMAN_H
#define OOP_LAB1_ELEPHANTMAN_H


#include "rider.h"
#include "../base/base.h"

class Base;

class ElephantMan : public Rider {
public:
    ElephantMan(Base *base);

    ~ElephantMan();

    char getType() override;

    void notify() override;

    int getBaseNum() override;

private:
    Base* view;
};


#endif //OOP_LAB1_ELEPHANTMAN_H
