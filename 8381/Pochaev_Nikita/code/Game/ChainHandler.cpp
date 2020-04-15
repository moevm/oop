#include "Game/ChainHandler.h"

IHandler* AbstractHandler::setNext(IHandler* handler)
{
    this->nextHandler = handler;
    return handler;
}
