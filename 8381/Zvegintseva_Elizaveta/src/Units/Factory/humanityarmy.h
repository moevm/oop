#ifndef HUMANITYARMY_H
#define HUMANITYARMY_H

#include "fantasyArmy.h"

#include <Units/Arrow/archer.h>

#include <Units/Cavelry/knigth.h>

#include <Units/Infantry/swardman.h>


class HumanityArmy: public FantasyArmy{
public:
    Arrow* createArrow();
    Cavelry* createCavelry();
    Infantry* createInfantry();
};

#endif // HUMANITYARMY_H
