//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_ELEPHANTMAN_H
#define OOP_LAB1_ELEPHANTMAN_H


#include "rider.h"

class ElephantMan : public Rider {
public:
    ElephantMan(int x, int y);
    char getType() override;
};


#endif //OOP_LAB1_ELEPHANTMAN_H
