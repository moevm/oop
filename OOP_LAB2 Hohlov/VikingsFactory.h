
#ifndef OOP_LAB1_VIKINGSFACTORY_H
#define OOP_LAB1_VIKINGSFACTORY_H

#include "UnitFactory.h"
#include "Berserk.h"
#include "SwordMan.h"

class VikingsFactory: public UnitFactory {

public:
    Berserk *createFirst(){ return new Berserk(); }
    SwordMan *createSecond(){ return new SwordMan(); }

};

#endif //OOP_LAB1_VIKINGSFACTORY_H
