//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_VILLAGE_H
#define MYGAME_VILLAGE_H


#include "NeutralObject.h"

class Village : public NeutralObject {
private:
    int goldPoints = 50;
    int *addressMoney = nullptr;
public:
    Village();
    void operator[](int *something) override ;
    void makeGameMove() override ;
};


#endif //MYGAME_VILLAGE_H
