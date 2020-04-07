#ifndef IFACADEMEDIATOR_H
#define IFACADEMEDIATOR_H

#include <string>

#include "InformationHeaders/commandPar.h"
#include "UIFacade.h"

class IFacadeMediator
{
public:
    virtual ~IFacadeMediator() = default;
    virtual UIFacade *getFacade() const = 0;
    virtual void sendString(Request request, std::string answer) = 0;
};

#endif // IFACADEMEDIATOR_H
