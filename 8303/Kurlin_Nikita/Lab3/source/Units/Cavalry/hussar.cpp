#include "hussar.h"

Hussar::Hussar()
{
    this->attributes = new Attributes;
    *(this->attributes) = { 20, 70, 15 };
    name = "Hussar";
}
