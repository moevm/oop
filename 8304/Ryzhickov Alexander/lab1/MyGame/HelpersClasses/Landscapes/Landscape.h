//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_LANDSCAPE_H
#define MYGAME_LANDSCAPE_H

#include "../../enums/kindLandscape.h"
#include "../../enums/kindUnit.h"

class Landscape {
public:
    kindLandscape landscape;
    virtual bool getInformationAboutLandscape() = 0;
    virtual int getBonus(kindUnit kindUnit) = 0;
};


#endif //MYGAME_LANDSCAPE_H
