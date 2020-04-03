#include "Object.h"

Point Object::get_coords() const {
    return this->coords;
}

ObjectType Object::type() const{
    return OBJECT;
}