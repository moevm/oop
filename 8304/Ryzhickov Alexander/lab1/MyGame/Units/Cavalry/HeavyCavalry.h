//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_HEAVYCAVALRY_H

#define MYGAME_HEAVYCAVALRY_H


#include "Cavalry.h"

class HeavyCavalry : public Cavalry {
public:
    HeavyCavalry(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);

    HeavyCavalry(const HeavyCavalry &heavyCavalry);

    HeavyCavalry(HeavyCavalry &&heavyCavalry);

    HeavyCavalry &operator=(const HeavyCavalry &heavyCavalry) {
        if (&heavyCavalry == this)
            return *this;

        delete unitPosition;
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
        return *this;
    }
    HeavyCavalry &operator=(HeavyCavalry &&heavyCavalry) {
        if (&heavyCavalry == this)
            return *this;

        delete unitPosition;
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
        unitPosition = nullptr;
        return *this;
    }
    void attack() override;
};


#endif //MYGAME_HEAVYCAVALRY_H
