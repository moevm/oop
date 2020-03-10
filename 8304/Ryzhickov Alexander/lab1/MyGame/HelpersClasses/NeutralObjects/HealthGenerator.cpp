#include "HealthGenerator.h"
//
// Created by Alex on 08.03.2020.
//

#include "HealthGenerator.h"
HealthGenerator::HealthGenerator() {
    isActive = true;
    countGameMoves = 0;
}

void HealthGenerator::operator[](int *something) {
    if(isActive) {
        *something = *something + healthPoints;
        isActive = false;
    }
}

void HealthGenerator::makeGameMove() {
    if (countGameMoves == 3) {
        isActive = true;
        countGameMoves = 0;
    }
    if (!isActive) {
        countGameMoves++;
    }
}