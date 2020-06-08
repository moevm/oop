//
// Created by therealyou on 11.03.2020.
//

#ifndef LAB1_MEDICINE_H
#define LAB1_MEDICINE_H


#include "Object.h"

class Medicine : public Object {
public:
    Medicine(int x, int y, int buffValue);
    char getChar() override;
};


#endif //LAB1_MEDICINE_H
