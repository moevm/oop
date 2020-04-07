#ifndef IGAMEMEDIATOR_H
#define IGAMEMEDIATOR_H

#include "GameField/Coords.h"
#include "InformationHeaders/commandPar.h"

class IGameMediator
{
public:
    virtual ~IGameMediator() = default;
    // FIXME: всё ли здесь верно передаётся?
    virtual void Notify(Coords coords, Request request) = 0;
};

#endif // IGAMEMEDIATOR_H
