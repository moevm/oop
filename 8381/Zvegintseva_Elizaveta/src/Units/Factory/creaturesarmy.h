#ifndef CREATURESARMY_H
#define CREATURESARMY_H

#include "fantasyArmy.h"

#include <Units/Arrow/shaman.h>

#include <Units/Cavelry/rider.h>

#include <Units/Infantry/ork.h>



class CreaturesArmy: public FantasyArmy{
    Arrow * createArrow();
    Cavelry * createCavelry();
    Infantry * createInfantry();
};

#endif // CREATURESARMY_H
