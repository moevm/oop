#include "swordsman.h"

Swordsman::Swordsman()
{
    this->attributes = new Attributes;
    *(this->attributes) = {50, 70, 20};
}
