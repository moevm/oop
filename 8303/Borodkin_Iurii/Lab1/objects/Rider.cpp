#include "Rider.h"
#include <utility>

Rider::Rider(std::pair<int, int> coords, std::string name) :
            Unit(coords, std::move(name))
{}

std::string Rider::type() const {return "Rider";}

void Rider::moveY(Rider::Moves y) {
    _coordinates.second += y;
}

void Rider::moveX(Rider::Moves x) {
    _coordinates.first  += x;
}
