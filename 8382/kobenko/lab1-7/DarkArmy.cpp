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

int DarkCavalry::MoveUnits(int x, int y) {
    try {
        if((this->x - x < 0 && this->x - x > 1) || (this->y - y < 0 && this->y - y > 1))
            throw "You went too far";
        this->x = x;
        this->y = y;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int DarkInfantry::MoveUnits(int x, int y) {
    try {
        if((this->x - x < 0 && this->x - x > 1) || (this->y - y < 0 && this->y - y > 1))
            throw "You went too far";
        this->x = x;
        this->y = y;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int DarkArcher::MoveUnits(int x, int y) {
    try {
        if((this->x - x < 0 && this->x - x > 1) || (this->y - y < 0 && this->y - y > 1))
            throw "You went too far";
        this->x = x;
        this->y = y;
    }
    catch (const char * exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    return 0;
}

int DarkCavalry::AttackUnits(){
    return this->attack;
}

int DarkInfantry::AttackUnits(){
    return this->attack;
}

int DarkArcher::AttackUnits(){
    return this->attack;
}

void DarkCavalry::getDamage(int attack){
    if (attack > this->armor)
        this->health = this->health - (attack - this->armor);
    if (this->health < 0)
        this->type = '.';
}

void DarkInfantry::getDamage(int attack) {
    if (attack > this->armor)
        this->health = this->health - (attack - this->armor);
    if (this->health < 0)
        this->type = '.';
}

void DarkArcher::getDamage(int attack) {
    if (attack > this->armor)
        this->health = this->health - (attack - this->armor);
    if (this->health < 0)
        this->type = '.';
}

