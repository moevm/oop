//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_FORESTLANDSCAPE_H
#define MYGAME_FORESTLANDSCAPE_H


#include "Landscape.h"

class ForestLandscape: public Landscape {
public:
    ForestLandscape();
    bool getInformationAboutLandscape() override;
    int getBonus(kindUnit kindUnit) override;
};


#endif //MYGAME_FORESTLANDSCAPE_H
