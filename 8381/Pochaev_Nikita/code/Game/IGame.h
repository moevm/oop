#ifndef IGAME_H
#define IGAME_H

#include "GameField/Coords.h"
#include "InformationHeaders/commandPar.h"

class UIFacade;

class IGame
{
public:
    virtual ~IGame() = default;
    virtual void createBase(Coords coords, BaseType type) = 0;
};

#endif // IGAME_H
