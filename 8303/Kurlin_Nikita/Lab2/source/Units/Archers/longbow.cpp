#include "longbow.h"

Longbow::Longbow()
{
    this->attributes = new Attributes;
    *(this->attributes) = { 15, 100, 10 };
}
