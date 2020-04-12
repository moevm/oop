#ifndef CHAINHANDLER_H
#define CHAINHANDLER_H

#include <string>

#include "Bases/GameBase.h"
#include "GameField/GameFieldProxy.h"
#include "InformationHeaders/commandPar.h"
#include "FacadeMediator.h"

class IHandler
{
public:
    virtual IHandler *setNext(IHandler *handler) = 0;
};

class AbstractHandler: public IHandler
{
protected:
    IHandler* nextHandler{};

public:
    AbstractHandler() = default;
    IHandler* setNext(IHandler* handler) override;
};

#endif // CHAINHANDLER_H
