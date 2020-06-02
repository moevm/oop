//
// Created by vlad on 01.06.2020.
//

#include "LightArmy.h"

LightCavalry::LightCavalry():type('c'), health(2), attack(3), armor(1), x(1), y(0){}
LightInfantry::LightInfantry():type('i'), health(2), attack(2), armor(1), x(0), y(1){}
LightArcher::LightArcher() : type('a'), health(3), attack(2), armor(0), x(1), y(1) {}

int LightCavalry::MoveUnits(int x, int y) {
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

int LightInfantry::MoveUnits(int x, int y) {
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

int LightArcher::MoveUnits(int x, int y) {
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

int LightCavalry::AttackUnits(){
    return this->attack;
}

int LightInfantry::AttackUnits(){
    return this->attack;
}

int LightArcher::AttackUnits(){
    return this->attack;
}

void LightCavalry::getDamage(int attack){
    if (attack > this->armor)
        this->health = this->health -  (attack - this->armor);
    if (this->health < 0)
        this->type = '.';
}

void LightInfantry::getDamage(int attack) {
    if (attack > this->armor)
        this->health = this->health - (attack - this->armor);
    if (this->health < 0)
        this->type = '.';
}

void LightArcher::getDamage(int attack) {
    if (attack > this->armor)
        this->health = this->health - (attack - this->armor);
    if (this->health < 0)
        this->type = '.';
}
