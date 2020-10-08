//
// Created by kot on 09.05.2020.
//

#include "proxy.h"


Proxy::Proxy (Landscape * landscape): landscape(landscape){}

Proxy::~Proxy () {delete  landscape;}


bool Proxy::checkAccess ()
{
    std::cout << "Proxy: checking access before real request. /n";
    return landscape != nullptr;
}

void Proxy::logAccess ()
{
    std::cout << "Proxy: request for landscape./n";
}

bool Proxy::canMove (Unit* unitType) const
{
    if(landscape->getType() == "Forest" || landscape->getType() == "Desert")
        return true;
    if((unitType->getType() == "Dragon" || unitType->getType() == "Chimera")
       && landscape->getType() == "River" ) return true;
    std::cout << "HE CAN NOT PASS\n";
    return false;
}

bool Proxy::canAttack (Unit* unitType){
    if (landscape->getType() == "Forest"
        && (unitType->getType() == "Dragon" || unitType->getType()== "Chimera"))
    {
        delete landscape;
        landscape = new Desert();
        return true;
    }
    return !(landscape->getType() == "Forest"
             && (unitType->getType() == "Dragon" || unitType->getType() == "Witch"));
}

std::string Proxy::getType() const
{
//    return  landscape->getType();
    switch (landscape->getType()[0]) {
        case 'R':
            return "〜〜〜〜";
        case 'D':
            return "_ǂ___@_";
        case 'F':
            return "↑↑_↑↑_↑";
    }
    return "ERROR";

}
