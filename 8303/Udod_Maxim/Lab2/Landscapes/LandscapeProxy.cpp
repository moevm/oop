//
// Created by shenk on 01.03.2020.
//

#include "LandscapeProxy.h"

LandscapeProxy::LandscapeProxy(Point position) {

    landscape = GameField::getInstance()->getCell(position)->getLandscape();

}

int LandscapeProxy::getDamageFactor(WeaponType type) {
    if (landscape) {
        return landscape->getDamageFactor(type);
    } else{
        return 1;
    }
}

int LandscapeProxy::getAbsorptionFactor(ArmorType type) {
    if (landscape) {
        return landscape->getAbsorptionFactor(type);
    } else{
        return 1;
    }}
