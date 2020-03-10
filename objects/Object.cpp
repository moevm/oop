#include "Object.h"
#include <utility>

Object::Object(std::string name) : _name(std::move(name))
{}

std::string& Object::name() {return _name;}

unsigned Object::health() const {return attr ? attr->health : 0;}

unsigned Object::range() const {return attr ? attr->range : 0;}

unsigned Object::damage() const {return attr ? attr->damage : 0;}

unsigned Object::armor() const {return attr ? attr->armor : 0;}

unsigned Object::mana() const {return attr ? attr->mana : 0;}

Object::~Object() {delete attr;}
