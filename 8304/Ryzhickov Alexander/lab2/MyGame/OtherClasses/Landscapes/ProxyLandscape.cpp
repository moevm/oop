//
// Created by Alex on 30.03.2020.
//

#include "ProxyLandscape.h"

ProxyLandscape::ProxyLandscape(Landscape *landscape) {
    this->landscape = landscape;
}

bool ProxyLandscape::getInformationAboutLandscape() {
    return landscape->getInformationAboutLandscape();
}

int ProxyLandscape::getBonus(Unit *unit) {
    unit->setAttackBonus(landscape->getBonus(unit));
    return 0;
}
