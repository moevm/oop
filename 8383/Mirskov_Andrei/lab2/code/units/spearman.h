//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_SPEARMAN_H
#define OOP_LAB1_SPEARMAN_H

#include "infantry.h"
#include "../base/base.h"

class Base;

class SpearMan : public Infantry {
public:
    SpearMan(Base *base);

    ~SpearMan();

    char getType() override ;

    void notify() override;

    int getBaseNum() override;

private:
    Base* view;
};


#endif //OOP_LAB1_SPEARMAN_H
