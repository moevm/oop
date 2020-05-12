#ifndef SAVESTUCTURES_H
#define SAVESTUCTURES_H

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "GameField/Coords.h"
#include "InformationHeaders/unitPar.h"
#include "InformationHeaders/commandPar.h"
#include "InformationHeaders/unitPar.h"

struct UnitParametersMemento
{
    eUnitsType type;
    std::string name;
    size_t health;
    size_t armor;
    size_t meleeAttackStrength;
    size_t movementRange;
    size_t actionTokens;

    Coords position;
    Coords creationBaseCoords;
};

struct UnitStorekeeperParametersMemento
{
    std::vector<std::string> unitAccountingInf;
};

struct BaseParametersCaretaker
{
    size_t health;
    eBaseType type;
    std::shared_ptr<UnitStorekeeperParametersMemento> unitCountsData;
};

struct FieldParametersMemento
{
    size_t unitsCount;
    size_t maxUnitsCount;
    size_t baseCount;
    size_t maxBaseCount;
    size_t width;
    size_t height;
    
    std::map<Coords, std::shared_ptr<BaseParametersCaretaker>> bases;
    std::map<Coords, std::shared_ptr<UnitParametersMemento>> units;
};

struct FieldProxyParametersMemento
{
    std::map<Coords, std::string> landscape;
    std::map<Coords, std::string> neutralObjects;
    std::shared_ptr<FieldParametersMemento> fieldParam;
};

struct GameParametersMemento
{
    size_t playersCount;
    std::map<std::string, Coords> baseNames;
    std::shared_ptr<FieldProxyParametersMemento> fieldParam;
};

#endif // SAVESTUCTURES_H
