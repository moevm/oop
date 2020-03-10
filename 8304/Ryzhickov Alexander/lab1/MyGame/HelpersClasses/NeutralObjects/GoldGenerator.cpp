//
// Created by Alex on 08.03.2020.
//

#include "GoldGenerator.h"

GoldGenerator::GoldGenerator() {
    isActive = true;
    countGameMoves = 0;
}

void GoldGenerator::operator[](int *something) {
    addressMoney = something;
}

void GoldGenerator::makeGameMove() {
    *addressMoney = *addressMoney + goldPoints;
}
