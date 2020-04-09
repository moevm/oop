//
// Created by Alex on 16.02.2020.
//

#include "HeavyCavalry.h"
#include "../../HelpersClasses/Data.h"

HeavyCavalry::HeavyCavalry(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) : Cavalry(startX, startY, unitWeapon, unitArmor) {
    setHealth(healthSwordmen);
    setMoves(movesHeavyCavalry);
}

HeavyCavalry::HeavyCavalry(const HeavyCavalry &heavyCavalry) {
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(heavyCavalry.unitPosition->getPositionX());
    unitPosition->setNewPositionY(heavyCavalry.unitPosition->getPositionY());
    unitArmor = heavyCavalry.unitArmor;
    unitWeapon = heavyCavalry.unitWeapon;
    health = heavyCavalry.getHealth();
    armor = heavyCavalry.getArmor();
    damage = heavyCavalry.getDamage();
    moves = heavyCavalry.getMoves();
    numerInArmy = heavyCavalry.getNumerInArmy();
}


HeavyCavalry::HeavyCavalry(HeavyCavalry &&heavyCavalry){
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(heavyCavalry.unitPosition->getPositionX());
    unitPosition->setNewPositionY(heavyCavalry.unitPosition->getPositionY());
    unitArmor = heavyCavalry.unitArmor;
    unitWeapon = heavyCavalry.unitWeapon;
    health = heavyCavalry.getHealth();
    armor = heavyCavalry.getArmor();
    damage = heavyCavalry.getDamage();
    moves = heavyCavalry.getMoves();
    numerInArmy = heavyCavalry.getNumerInArmy();

    heavyCavalry.unitPosition = nullptr;
}

void HeavyCavalry::attack() {

}

