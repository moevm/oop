#include "Object.h"
#include <utility>

Object::Object(string name) : _name(std::move(name))
{}

bool Object::createUnit(Unit*) {return false;}

Unit* Object::getUnit() {return nullptr;}

string& Object::name() {return _name;}

int Object::health() const {return attr ? attr->health : 0;}

unsigned Object::range() const {return attr ? attr->range : 0;}

unsigned Object::damage() const {return attr ? attr->damage : 0;}

unsigned Object::armor() const {return attr ? attr->armor : 0;}

unsigned Object::mana() const {return attr ? attr->mana : 0;}

bool Object::empty() const { return attr == nullptr; }

Object::~Object()
{
    delete attr;
}

Object& operator+=(Object& unit, Pack& pack)
{
    *(unit.attr) = *(unit.attr) + pack.buff();
    return unit;
}
