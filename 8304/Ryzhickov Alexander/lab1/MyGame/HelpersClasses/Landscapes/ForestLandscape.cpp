//
// Created by Alex on 08.03.2020.
//

#include "ForestLandscape.h"

ForestLandscape::ForestLandscape() {
   ForestLandscape::landscape= kindLandscape ::forest;
}

bool ForestLandscape::getInformationAboutLandscape() {
    return true;
}

int ForestLandscape::getBonus(kindUnit kindUnit) {
    if(kindUnit==kindUnit::Archer || kindUnit==kindUnit::Arbalester){
        return 20;
    } else{
        return 0;
    }
}
