#ifndef OOP_LAB1_WIZARDFACTORY_H
#define OOP_LAB1_WIZARDFACTORY_H

#include "UnitFactory.h"
#include "../Unit/Wizard/IceMage.h"
#include "../Unit/Wizard/FireMage.h"

class WizardFactory : public UnitFactory {

 public:

  IceMage *createFirst() {
    return new IceMage();
  }
  FireMage *createSecond() {
    return new FireMage();
  }
};

#endif //OOP_LAB1_WIZARDFACTORY_H