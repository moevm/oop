//
// Created by Alex on 21.03.2020.
//

#include "FieldLandscape.h"
#include "typeinfo"
#include "../../Units/HeavyInfantry/HeavyInfantry.h"

bool FieldLandscape::getInformationAboutLandscape() {
    return true;
}

int FieldLandscape::getBonus(Unit *unit) {
    if (dynamic_cast<HeavyInfantry *>(unit) != nullptr) {
        return 25;
    } else {
        return 0;
    }
}
