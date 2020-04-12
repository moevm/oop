#ifndef IFACADEMEDIATOR_H
#define IFACADEMEDIATOR_H

#include <string>

#include "InformationHeaders/commandPar.h"
#include "UIFacade.h"

class IFacadeMediator
{
public:
    virtual ~IFacadeMediator() = default;
    virtual std::string sendRequest(std::vector<size_t> param, eUnitsType unitType_ = NONE_UNIT, eBaseType baseType_ = NONE_BASE) = 0;
    virtual std::string sendInfoRequest(eRequest request, size_t x = 0, size_t y = 0) = 0;
};

#endif // IFACADEMEDIATOR_H
