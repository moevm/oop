#ifndef IGAME_H
#define IGAME_H

#include <QString>

#include "GameField/Coords.h"
#include "InformationHeaders/commandPar.h"
#include "InformationHeaders/unitPar.h"
#include "Game/Saving/SaveStuctures.h"

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

class IGameInfo
{
public:
    virtual std::string getGameInf() = 0;
    virtual std::string getBaseInfo(size_t x, size_t y) = 0;
    virtual std::string getUnitInfo(size_t x, size_t y) = 0;
    virtual std::string getItemInfo(size_t x, size_t y) = 0;
    virtual std::string getLandInfo(size_t x, size_t y) = 0;

    virtual size_t getPlayersCount() = 0;
};

class IGameMemento
{
public:
    virtual std::shared_ptr<GameParametersMemento> createMemento() = 0;
    virtual void restoreMemento(std::shared_ptr<GameParametersMemento> memento) = 0;
};

#endif // IGAME_H
