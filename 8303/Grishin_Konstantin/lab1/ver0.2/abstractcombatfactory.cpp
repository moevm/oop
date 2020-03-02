#include "abstractcombatfactory.h"

#include "weapon.h"
#include "Units/melee.h"
#include "Units/range.h"
#include "Units/nuker.h"

#include "RedUnits/redarcher.h"
#include "RedUnits/redbarbarian.h"
#include "RedUnits/redberserker.h"

#include "BluUnits/bluarcher.h"
#include "BluUnits/blubarbarian.h"
#include "BluUnits/bluberserker.h"

Barbarian *NeutralCombatFactory::createBarbarian(Cell *cell, const std::string &weapon_name){
    MeleeWeapon *weapon;
    if(weapon_name == "club")
        weapon = new Club;
    else if (weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new Barbarian(cell, weapon);
}


Archer* NeutralCombatFactory::createArcher(Cell *cell, const std::string &weapon_name){
    RangeWeapon *weapon;
    if(weapon_name == "bow"){
        weapon = new Bow();
    }
    else if(weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new Archer(cell, weapon);
}


Berserker* NeutralCombatFactory::createBerserker(Cell *cell, const std::string &weapon_name){
    NukerWeapon *weapon;
    if(weapon_name == "scythe")
        weapon = new Scythe;
    else if(weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new Berserker(cell, weapon);
}



// RED
Barbarian *RedCombatFactory::createBarbarian(Cell *cell, const std::string &weapon_name){
    MeleeWeapon *weapon;
    if(weapon_name == "club")
        weapon = new Club;
    else if (weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new RedBarbarian(cell, weapon);
}


Archer* RedCombatFactory::createArcher(Cell *cell, const std::string &weapon_name){
    RangeWeapon *weapon;
    if(weapon_name == "bow"){
        weapon = new Bow();
    }
    else if(weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new RedArcher(cell, weapon);
}


Berserker* RedCombatFactory::createBerserker(Cell *cell, const std::string &weapon_name){
    NukerWeapon *weapon;
    if(weapon_name == "scythe")
        weapon = new Scythe;
    else if(weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new RedBerserker(cell, weapon);
}


//BLU
Barbarian *BluCombatFactory::createBarbarian(Cell *cell, const std::string &weapon_name){
    MeleeWeapon *weapon;
    if(weapon_name == "club")
        weapon = new Club;
    else if (weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new BluBarbarian(cell, weapon);
}


Archer* BluCombatFactory::createArcher(Cell *cell, const std::string &weapon_name){
    RangeWeapon *weapon;
    if(weapon_name == "bow"){
        weapon = new Bow();
    }
    else if(weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new BluArcher(cell, weapon);
}


Berserker* BluCombatFactory::createBerserker(Cell *cell, const std::string &weapon_name){
    NukerWeapon *weapon;
    if(weapon_name == "scythe")
        weapon = new Scythe;
    else if(weapon_name == "nothing")
        weapon = nullptr;
    else
        return nullptr;

    return new BluBerserker(cell, weapon);
}

