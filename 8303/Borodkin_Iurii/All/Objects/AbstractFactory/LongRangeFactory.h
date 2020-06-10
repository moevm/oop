#ifndef LONGRANGEFACTORY_H
#define LONGRANGEFACTORY_H

#include "../Units/Archer.h"
#include "../Units/Wizard.h"

class LongRangeFactory
{
public:
    Unit* createArcher();
    Unit* createWizard();
};

#endif // LONGRANGEFACTORY_H
