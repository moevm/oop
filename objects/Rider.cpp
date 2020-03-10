#include "Rider.h"
#include <utility>

Rider::Rider(std::string name) : Unit(std::move(name))
{}

std::string Rider::type() const {return "Rider";}
