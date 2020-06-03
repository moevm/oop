//
// Created by vlad on 02.06.2020.
//

#include "DarkBase.h"

DarkBase::DarkBase():x(9), y(9), health(1), type('B'){}

int DarkBase::CreateUnits() {
    int tmp = rand()%3;
    return tmp;
}

DarkArcher DarkBase::createDarkArcher(){
    DarkArcher da;
    return da;
}

DarkCavalry DarkBase::createDarkCavalry(){
    DarkCavalry dc;
    return dc;
}

DarkInfantry DarkBase::createDarkInfantry(){
    DarkInfantry di;
    return di;
}

int DarkBase::checkBase() const{
    if (this->health <= 0)
        return 1;
}

void DarkBase::getDamage(int attack) {
    this->type = '.';
    this->health -= attack;
}

int DarkBase::ControlUnits(Field& field) {
    int count = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            if (field.field[i][j] == 'a' || field.field[i][j] == 'c' || field.field[i][j] == 'i')
                count++;
    }
    return count;
}