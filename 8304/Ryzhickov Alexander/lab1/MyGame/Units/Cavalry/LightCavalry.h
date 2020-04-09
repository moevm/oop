//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_LIGHTCAVALRY_H

#define MYGAME_LIGHTCAVALRY_H


#include "Cavalry.h"

class LightCavalry : public Cavalry {
public:
    LightCavalry(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);
    LightCavalry(const LightCavalry &lightCavalry);
    LightCavalry(LightCavalry &&lightCavalry);
    LightCavalry &operator=(const LightCavalry&lightCavalry) {
        if (&lightCavalry == this)
            return *this;

        delete unitPosition;
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
        return *this;

    }
    LightCavalry &operator=(LightCavalry &&lightCavalry) {
        if (&lightCavalry == this)
            return *this;

        delete unitPosition;
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
        return *this;

    }
    void attack() override;
};


#endif //MYGAME_LIGHTCAVALRY_H
