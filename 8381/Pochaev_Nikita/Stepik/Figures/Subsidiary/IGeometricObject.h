#ifndef STEPIC_IGEOMETRICOBJECT_H
#define STEPIC_IGEOMETRICOBJECT_H

#include <string>

#include "Information.h"

class IGeometryObject
{
public:
    virtual ~IGeometryObject() = default;
    virtual eFIGURE getType() const = 0;
    virtual std::string getDescription() const = 0;
};

#endif //STEPIC_IGEOMETRICOBJECT_H
