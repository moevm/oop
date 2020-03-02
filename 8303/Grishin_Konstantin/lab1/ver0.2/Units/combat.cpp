#include "Units/combat.h"

#include "weapon.h"
#include "cell.h"

Combat::~Combat(){
    if(weapon != nullptr)
        delete weapon;
}


Combat::Combat(Cell *cell, Combat::Type combType):
    Unit(cell, Unit::Combat), combType(combType)
{}


Combat::Type Combat::getCombatType() const{
    return combType;
}


void Combat::setWeapon(Weapon *weapon){
    if(this->weapon != nullptr){
        delete this->weapon;
    }
    this->weapon = weapon;
}


const Weapon* Combat::getWeapon() const{
    return weapon;
}


void Combat::setMode(bool bMode){
    this->bMode = bMode;
}


bool Combat::getMode() const{
    return bMode;
}

