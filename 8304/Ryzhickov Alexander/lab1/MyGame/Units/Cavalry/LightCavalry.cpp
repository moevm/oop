//
// Created by Alex on 16.02.2020.
//

#include "LightCavalry.h"
#include "../../Trappings/Weapons/MeleeWeapons/Sword.h"
#include "../../HelpersClasses/Data.h"

LightCavalry::LightCavalry(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) : Cavalry(startX, startY, unitWeapon, unitArmor) {
    setHealth(healthSwordmen);
    setMoves(movesLightCavalry);
}

LightCavalry::LightCavalry(const LightCavalry &lightCavalry) {
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(lightCavalry.unitPosition->getPositionX());
    unitPosition->setNewPositionY(lightCavalry.unitPosition->getPositionY());
    unitArmor = lightCavalry.unitArmor;
    unitWeapon = lightCavalry.unitWeapon;
    health = lightCavalry.getHealth();
    armor = lightCavalry.getArmor();
    damage = lightCavalry.getDamage();
    moves = lightCavalry.getMoves();
    numerInArmy = lightCavalry.getNumerInArmy();
}

LightCavalry::LightCavalry(LightCavalry &&lightCavalry)  {
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(lightCavalry.unitPosition->getPositionX());
    unitPosition->setNewPositionY(lightCavalry.unitPosition->getPositionY());
    unitArmor = lightCavalry.unitArmor;
    unitWeapon = lightCavalry.unitWeapon;
    health = lightCavalry.getHealth();
    armor = lightCavalry.getArmor();
    damage = lightCavalry.getDamage();
    moves = lightCavalry.getMoves();
    numerInArmy = lightCavalry.getNumerInArmy();

    lightCavalry.unitPosition = nullptr;
}

void LightCavalry::attack() {

}
