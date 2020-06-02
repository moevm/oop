#ifndef FANTASYARMY_H
#define FANTASYARMY_H

#include <Units/Arrow/arrow.h>
#include <Units/Cavelry/cavelry.h>
#include <Units/Infantry/infantry.h>

class FantasyArmy{
public:
    virtual ~FantasyArmy()=default;
    virtual Arrow* createArrow()=0;
    virtual Cavelry* createCavelry()=0;
    virtual Infantry* createInfantry()=0;
};
#endif // FANTASYARMY_H
