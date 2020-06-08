#include "unit.h"

void Unit::move(int x, int y) {
    this->x = x;// - 1;
    this->y = y;// - 1;
}

Scorpio::Scorpio() {
    this->type = "MeleeWarrior";
    this->name = "scorpio";
    this->health = 1001;
    this->armor = 50;
    this->attack = 30;
}

Mammoth::Mammoth() {
    this->type = "MeleeWarrior";
    this->name = "mammoth";
    this->health = 200;
    this->armor = 70;
    this->attack = 50;
}

Frog::Frog() {
    this->type = "MediumWarrior";
    this->name = "frog";
    this->health = 100;
    this->armor = 50;
    this->attack = 10;
}

Kangaroo::Kangaroo() {
    this->type = "MediumWarrior";
    this->name = "kangaroo";
    this->health = 100;
    this->armor = 5;
    this->attack = 67;
}

Swallow::Swallow() {
    this->type = "DistanceWarrior";
    this->name = "swallow";
    this->health = 100;
    this->armor = 50;
    this->attack = 30;
}

Hawk::Hawk() {
    this->type = "DistanceWarrior";
    this->name = "hawk";
    this->health = 100;
    this->armor = 50;
    this->attack = 30;
}
