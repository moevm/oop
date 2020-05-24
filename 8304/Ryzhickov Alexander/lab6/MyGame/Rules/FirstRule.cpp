//
// Created by Alex on 11.05.2020.
//

#include "FirstRule.h"
#include "../Units/Unit.h"

void FirstRule::getStartUnitPack(int *arrayUnit) {
    arrayUnit[0] = 1; //Spearmen
    arrayUnit[1] = 1; //Swordmen
    arrayUnit[2] = 1; //King
    arrayUnit[3] = 1; //Knight
    arrayUnit[4] = 1; //Archer
    arrayUnit[5] = 1; //Magician
}

int FirstRule::getStartMoney() {
    return 1000;
}

bool FirstRule::checkEndGame(int *unitMoneyAdress, int *adressMoney) {
    if (unitMoneyAdress != nullptr) {
        if (unitMoneyAdress == adressMoney){
            return true;
        }
    }
    return false;
}

int FirstRule::getOrder() {
    return 1;
}


