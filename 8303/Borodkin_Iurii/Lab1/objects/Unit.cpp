#include "Unit.h"

Unit::Unit(std::pair<int, int> coordinates, std::string name) :
            Object(coordinates, std::move(name)), _attack(0)
{}

std::string Unit::type() const {return "Unit";}
