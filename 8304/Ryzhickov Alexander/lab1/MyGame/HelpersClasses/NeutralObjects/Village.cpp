//
// Created by Alex on 08.03.2020.
//

#include "Village.h"
Village::Village() {
    isActive = true;
    countGameMoves = 0;
}

void Village::operator[](int *something) {
    addressMoney = something;
}

void Village::makeGameMove() {
    *addressMoney = *addressMoney + goldPoints;
}