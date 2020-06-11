//
// Created by anton on 11.03.2020.
//

#include "Neutral.h"
char ForcePortion::getType() const {
    return 'f';
}

char Stew::getType() const {
    return 's';
}

char Poison::getType() const {
    return 'p';
}

char RangePortion::getType() const {
    return 'r';
}

void ForcePortion::getEffect(Unit* tmp) {
    tmp->values.attack += 10;
}

void Stew::getEffect(Unit* tmp) {
    tmp->values.health += 20;
}

void Poison::getEffect(Unit* tmp) {
    tmp->values.health -= 15;
    tmp->values.attack -= 5;
}

void RangePortion::getEffect(Unit* tmp) {
    tmp->values.attackRange += 1;
}

void Neutral::operator+=(Unit *tmp) {
    this->getEffect(tmp);
}