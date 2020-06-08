#include "landscape.h"


Landscape::Landscape(const std::string& id,
                     Type type,
                     float fMoveCost,
                     float fOutDmgMod,
                     float fInDmgMod):
    id(id), type(type), fMoveCost(fMoveCost), fOutDmgMod(fOutDmgMod), fInDmgMod(fInDmgMod)
{}

const std::string& Landscape::getID() const{
    return id;
}


Landscape::Type Landscape::getType() const{
    return type;
}


float Landscape::getMoveCost() const{
    return fMoveCost;
}


float Landscape::getOutDmgMod() const{
    return fOutDmgMod;
}


float Landscape::getInDmgMod() const{
    return fInDmgMod;
}
