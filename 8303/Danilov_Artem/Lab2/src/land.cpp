#include "land.h"

std::string River::getType() const
{
    return  type;
}


std::string Forest::getType() const
{
    return  type;
}


std::string Desert::getType() const
{
    return  type;
}

Proxy::Proxy(std::string type)
{
    switch (type[0]) {
    case 'R':
        landscape = new River;
        break;
    case 'D':
        landscape = new Desert;
        break;
    case 'F':
        landscape = new Forest;
    }
}

bool Proxy::checkMoveAccess(std::string unitType) const
{
    if(landscape->getType() == "F" || landscape->getType() == "D") return true;
    if((unitType == "DRN" || unitType == "CHR") && landscape->getType() == "R" ) return true;
    std::cout << "HE CAN NOT PASS\n";
    return false;

}

bool Proxy::checkAttackAccess(std::string unitType) const
{
    if (landscape->getType() == "F" && (unitType == "DRN" || unitType == "CHR")) {
        //delete landscape;
        //landscape->type = Desert
        return true;
    }
    if (landscape->getType() == "F" && (unitType == "DRD" || unitType == "WCH")) return false;
    return true;
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
        return "↑↑↑_↑↑_↑";
    }
    return "ERROR";

}
