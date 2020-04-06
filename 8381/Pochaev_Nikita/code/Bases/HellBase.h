#ifndef OOP_HELLBASE_H
#define OOP_HELLBASE_H

#include "GameBase.h"
#include "Units/ObjectFactory.h"
#include "Units/Unit.h"

class HellBase : public GameBase
{
public:
    HellBase() = default;
    ~HellBase() override = default;
    void describeYourself() override;
};

#endif //OOP_HELLBASE_H
