//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_MOUNTAINLANDSCAPE_H
#define MYGAME_MOUNTAINLANDSCAPE_H


#include "Landscape.h"

class MountainLandscape: public Landscape{
public:
    MountainLandscape();
    bool getInformationAboutLandscape() override;
    int getBonus(kindUnit kindUnit) override;
};


#endif //MYGAME_MOUNTAINLANDSCAPE_H
