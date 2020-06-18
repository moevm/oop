//
// Created by anton on 11.03.2020.
//

#include <cstdio>
#include "Landscape.h"

char Mountains::getType() const {
    return 'M';
}

char Grass::getType() const {
    return 'G';
}

char Forest::getType() const {
    return 'F';
}

bool Mountains::isAvailable(const Unit* tmp) const {
    return tmp->getClass() != 'p' && tmp->getClass() != 'b';
}

bool Grass::isAvailable(const Unit* tmp) const {
    return true;
}

bool Forest::isAvailable(const Unit* tmp) const {
    return tmp->getClass() != 'f';
}

void Grass::impact(Unit* tmp) {
//no impact
}

void Forest::impact(Unit* tmp) {
    if(tmp->getClass() == 'e' || tmp->getClass() == 'n')
    {
        tmp->values.health += 15;
    }// passive healing
}

void Mountains::impact(Unit* tmp) {
    if(tmp->getClass() == 'g')
    {
        tmp->values.health += 15;
    }
}