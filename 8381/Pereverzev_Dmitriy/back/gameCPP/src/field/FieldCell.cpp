#include "FieldCell.hpp"

FieldCell::FieldCell()
{
    this->object = nullptr;
    int val = rand() % 4;

    this->landscape = new LandscapeProxy(val);
}

FieldCell::FieldCell(Object *object, Landscape *landscape)
{
    this->object = object;
    this->landscape = landscape;
}

FieldCell::~FieldCell()
{
    delete object;
    delete landscape;
}
void FieldCell::setObject(Object *object)
{
    this->object = object;
}

void FieldCell::setLandscape(Landscape *landscape)
{
    this->landscape = landscape;
}

Object *FieldCell::getObject()
{
    return this->object;
}
Landscape *FieldCell::getLandscape()
{
    return this->landscape;
}
