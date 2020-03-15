#include "dragoon.h"

Dragoon::Dragoon()
{
    this->attributes = new Attributes;
    *(this->attributes) = { 30, 70, 25 };
    name = "Dragoon";
}
