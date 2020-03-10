#ifndef LONGRANGEFACTORY_H
#define LONGRANGEFACTORY_H

#include "objects/Archer.h"
#include "objects/Wizard.h"

class LongRangeFactory
{
public:
    Object* createArcher();
    Object* createWizard();
};

#endif // LONGRANGEFACTORY_H
