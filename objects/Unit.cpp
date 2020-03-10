#include "Unit.h"

Unit::Unit(std::string name) : Object(std::move(name))
{}

std::string Unit::type() const {return "Unit";}
