#include "unit.h"

void Unit::move(int x, int y) {
    this->x = x - 1;
    this->y = y - 1;
}

Scorpio::Scorpio() {
    //this->x = x;
    //this->y = y;
    this->type = "MeleeWarrior";
    this->name = "scorpio";
    this->health = 100;
    this->armor = 50;
    this->attack = 30;
}

Mammoth::Mammoth() {
    //this->x = x;
    //this->y = y;
    this->type = "MeleeWarrior";
    this->name = "mammoth";
    this->health = 200;
    this->armor = 70;
    this->attack = 50;
}

Frog::Frog() {
    //this->x = x;
    //this->y = y;
    this->type = "MediumWarrior";
    this->name = "frog";
    this->health = 100;
    this->armor = 50;
    this->attack = 10;
}

Kangaroo::Kangaroo() {
    //this->x = x;
    //this->y = y;
    this->type = "MediumWarrior";
    this->name = "kangaroo";
    this->health = 100;
    this->armor = 5;
    this->attack = 67;
}

Swallow::Swallow() {
    //this->x = x;
    //this->y = y;
    this->type = "DistanceWarrior";
    this->name = "swallow";
    this->health = 100;
    this->armor = 50;
    this->attack = 30;
}

Hawk::Hawk() {
    //this->x = x;
    //this->y = y;
    this->type = "DistanceWarrior";
    this->name = "hawk";
    this->health = 100;
    this->armor = 50;
    this->attack = 30;
}
