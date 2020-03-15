#include "spearman.h"

Spearman::Spearman()
{
    this->attributes = new Attributes;
    *(this->attributes) = { 45, 70, 15 };
    name = "Spearman";
}
