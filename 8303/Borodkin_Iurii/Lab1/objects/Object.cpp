#include "Object.h"
#include <utility>

Object::Object(std::pair<int, int> coordinates, std::string name) :
                _coordinates(coordinates), _name(std::move(name)), _health(0)
{}

std::string& Object::name() {return _name;}

std::string Object::type() const {return "Object";}

unsigned Object::health() const {return _health;}

std::pair <int, int> Object::coordinates() const {return _coordinates;}


void Object::moveX(Object::Moves x) {
    _coordinates.first  += x;
}

void Object::moveY(Object::Moves y) {
    _coordinates.second += y;
}
