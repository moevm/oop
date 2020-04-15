#ifndef OOP_NEUTRALOBJECT_H
#define OOP_NEUTRALOBJECT_H

#include "Units/Unit.h"
#include "InformationHeaders/constPar.h"

class NeutralObject
{
public:
    virtual ~NeutralObject() = default;
    virtual void operator+= (const std::shared_ptr<Unit> &unit) = 0;
    virtual std::string getNameOfNeutralObject() = 0;
};

#endif //OOP_NEUTRALOBJECT_H
