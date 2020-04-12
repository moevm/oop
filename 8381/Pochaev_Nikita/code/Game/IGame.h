#ifndef IGAME_H
#define IGAME_H

#include <QString>

#include "GameField/Coords.h"
#include "InformationHeaders/commandPar.h"
#include "InformationHeaders/unitPar.h"

class UIFacade;

class IGame
{
public:
    virtual ~IGame() = default;
    virtual void createBase(eBaseType type, size_t xCoord, size_t yCoord, QString mame) = 0;
    virtual void createUnit(eUnitsType, size_t xCoord, size_t yCoord) = 0;
    virtual void moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDist) = 0;
    virtual void unitAttack(size_t xSource, size_t ySource, size_t xDest, size_t yDist) = 0;
};

#endif // IGAME_H
