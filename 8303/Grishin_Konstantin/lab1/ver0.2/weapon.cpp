#include "weapon.h"


//// ABSTRACT WEAPON
Weapon::Weapon(Type wType, int iDamage, int iMaxRange, const std::string& name):
    name(name), wType(wType), iDamage(iDamage), iMaxRange(iMaxRange)
{}


int Weapon::damage() const{
    return iDamage;
}


int Weapon::maxRange() const{
    return iMaxRange;
}


const std::string& Weapon::getName() const{
    return name;
}


//// ABSTRACT MELEE WEAPON
MeleeWeapon::MeleeWeapon(Type wType, int iDamage, const std::string& name):
    Weapon(wType, iDamage, 1, name), bDefenseMode(0)
{}


void MeleeWeapon::changeMode(){
    bDefenseMode = !bDefenseMode;
}


bool MeleeWeapon::mode(){
    return bDefenseMode;
}




//// CONCRETE MELEE WEAPON: CLUB
Club::Club():
    MeleeWeapon(Type::physical, 5, "club")
{}


float Club::fire(const Unit &enemy) const{
    return damage() * 1.f;
}


//// ABSTRACT RANGE WEAPON
RangeWeapon::RangeWeapon(Type type, int iDamage, int iMaxRange, int iBlindZone, const std::string& name):
    Weapon(type, iDamage, iMaxRange, name), iBlindZone(iBlindZone)
{}


//// CONCRETE RANGE WEAPON: BOW
Bow::Bow():
    RangeWeapon(Type::physical, 8, 2, 0, "bow")
{}


float Bow::fire(const Unit &enemy) const{
    return damage() * 1.f;
}


//// ABSTRACT NUKER WEAPON
NukerWeapon::NukerWeapon(Type type, int iDamage, int iMaxRange, int iBlindZone, const std::string& name):
    Weapon(type, iDamage, iMaxRange, name), iBlindZone(iBlindZone)
{}


//// CONCRETE NUKER WEAPON: SCYTHE
Scythe::Scythe():
    NukerWeapon(Type::physical, 4, 1, 0, "scythe")
{}


float Scythe::fire(const Unit& enemy) const{
    return damage() * 1.f;
}



