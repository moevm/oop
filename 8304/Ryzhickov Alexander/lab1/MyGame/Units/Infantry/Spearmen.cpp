//
// Created by Alex on 16.02.2020.
//

#include "Spearmen.h"
#include "../../Trappings/Weapons/MeleeWeapons/Spear.h"
#include "../../HelpersClasses/Data.h"

Spearmen::Spearmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : Infantry(startX, startY, unitWeapon,
                                                                                            unitArmor) {
    setHealth(healthSwordmen);
}

void Spearmen::stronger() {

}

Spearmen::Spearmen(const Spearmen &spearmen) {
    unitPosition = new Position(0, 0);
    unitWeapon = new Spear();
    unitPosition->setNewPositionX(spearmen.unitPosition->getPositionX());
    unitPosition->setNewPositionY(spearmen.unitPosition->getPositionY());
    unitArmor = spearmen.unitArmor;
    unitWeapon = spearmen.unitWeapon;
    health = spearmen.getHealth();
    armor = spearmen.getArmor();
    damage = spearmen.getDamage();
    moves = spearmen.getMoves();
    numerInArmy = spearmen.getNumerInArmy();
}

Spearmen::Spearmen(Spearmen &&spearmen)  {
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(spearmen.unitPosition->getPositionX());
    unitPosition->setNewPositionY(spearmen.unitPosition->getPositionY());
    unitArmor = spearmen.unitArmor;
    unitWeapon = spearmen.unitWeapon;
    health = spearmen.getHealth();
    armor = spearmen.getArmor();
    damage = spearmen.getDamage();
    moves = spearmen.getMoves();
    numerInArmy = spearmen.getNumerInArmy();
    spearmen.unitPosition = nullptr;
}

void Spearmen::attack() {

}

