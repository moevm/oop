//
// Created by vlad on 01.06.2020.
//

#include "DarkArmy.h"

DarkCavalry::DarkCavalry() {
    type = 'C';
    health = 2;
    attack = 3;
    armor = 1;
    x = 9;
    y = 8;
}

DarkInfantry::DarkInfantry() {
    type = 'I';
    health = 2;
    attack = 2;
    armor = 1;
    x = 8;
    y = 9;
}

DarkArcher::DarkArcher() {
    type = 'A';
    health = 2;
    attack = 2;
    armor = 0;
    x = 8;
    y = 8;
}

int DarkCavalry::MoveUnits(int a, int b) {
    try {
        if((abs(this->x - a) > 2) || (abs(this->y - b) > 2))
            throw "You went too far";
        this->x = a;
        this->y = b;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int DarkInfantry::MoveUnits(int a, int b) {
    try {
        if((abs(this->x - a) > 1) || (abs(this->y - b) > 1))
            throw "You went too far";
        this->x = a;
        this->y = b;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int DarkArcher::MoveUnits(int a, int b) {
    try {
        if((abs(this->x - a) > 1) || (abs(this->y - b) > 1))
            throw "You went too far";
        this->x = a;
        this->y = b;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int DarkCavalry::AttackUnits(char** field, char choose){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field[i][j] == choose){
                if (1 >= abs(x - i)) {
                    if (1 >= abs(y - j))
                        return this->attack;
                }
            }
        }
    }
    return -1;
}

int DarkInfantry::AttackUnits(char** field, char choose){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field[i][j] == choose){
                if (abs(x - i) <= 1) {
                    if (abs(y - j) <= 1)
                        return this->attack;
                }
            }
        }
    }
    return -1;
}

int DarkArcher::AttackUnits(char** field, char choose){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field[i][j] == choose){
                if (abs(x - i) <= 2) {
                    if (abs(y - j) <= 2)
                        return this->attack;
                }
            }
        }
    }
    return -1;
}

void DarkCavalry::getDamage(int att){
    if (att > this->armor)
        this->health = this->health - (att - this->armor);
    if (this->health <= 0)
        this->type = '.';
}

void DarkInfantry::getDamage(int att) {
    if (att > this->armor)
        this->health = this->health - (att - this->armor);
    if (this->health <= 0)
        this->type = '.';
}

void DarkArcher::getDamage(int att) {
    if (att > this->armor)
        this->health = this->health - (att - this->armor);
    if (this->health <= 0)
        this->type = '.';
}

