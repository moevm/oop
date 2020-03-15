#include "flatbow.h"

Flatbow::Flatbow()
{
    this->attributes = new Attributes;
    *(this->attributes) = { 20, 80, 10 };
    name = "Flatbow";
}
