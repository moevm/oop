#include "game.h"
#include "FacadeMediator.h"

Game::Game(size_t fieldHeight, size_t fieldWidth, bool fill)
{
    field = std::make_shared<GameFieldProxy>(fieldHeight, fieldWidth, fill);
}

Game::Game(size_t fieldHeight, size_t fieldWidth, size_t playersCount_, bool fill)
{
    playersCount = playersCount_;
    field = std::make_shared<GameFieldProxy>(fieldHeight, fieldWidth, fill);
}

std::shared_ptr<GameFieldProxy> Game::getField() const
{
    return field;
}

std::map<QString, BaseInf> Game::getBases() const
{
    return bases;
}

void Game::createBase(eBaseType type, size_t xCoord, size_t yCoord, QString srcBaseName)
{
    if(bases.find(srcBaseName) != bases.end())
    {
        throw std::invalid_argument("Base with this name already exists");
    }
    std::string baseType = "NULL";
    std::shared_ptr<GameBase> base;
    switch(type)
    {
        case HELL_BASE:
            baseType = "Hell Base";
            master.setBaseBuilder(&hellBaseBuilder);
            master.constructBase();
            base = master.getBase();
            break;
        case HUMAN_BASE:
            baseType = "Human Base";
            master.setBaseBuilder(&humanBaseBuilder);
            master.constructBase();
            base = master.getBase();
            break;
        case NONE_BASE:
            // TODO: tell what we don't have correct type of base
            return;
    }
    field->addBase(base, xCoord, yCoord);
    bases.insert(std::make_pair(srcBaseName, BaseInf(std::move(base), xCoord, yCoord)));
}

bool Game::getBaseCoordsByName(QString sourceBaseName, Coords &coords)
{
    coords.x = bases[sourceBaseName].xCoord;
    coords.y = bases[sourceBaseName].yCoord;

    return true;
}

void Game::createUnit(eUnitsType unitType, size_t xCoord, size_t yCoord)
{
    if(bases.size() == 0)
    {
        throw std::invalid_argument("Not a single base has been created, unit creation is not available");
    }
    std::shared_ptr<Unit> unit = field->getBaseByCoords(xCoord, yCoord)->getUnit(unitType);
    field->addUnit(unit, xCoord, yCoord);
    field->getUnitByCoords(xCoord, yCoord)->setBaseCreationCoords(Coords(xCoord, yCoord));
}

void Game::moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDist)
{
    field->moveUnit(xSource, ySource, xDest, yDist);
}

void Game::unitAttack(size_t xSource, size_t ySource, size_t xDest, size_t yDist)
{
    field->meleeAttackUnit(xSource, ySource, xDest, yDist);
}

std::string Game::getGameInf()
{
    // TODO: count of players, step and other
    return "Game info";
}

std::string Game::getBaseInfo(size_t x, size_t y)
{
    return field->getInfAboutBase(x, y);
}

std::string Game::getUnitInfo(size_t x, size_t y)
{
    return field->getInfAboutUnit(x, y);
}

std::string Game::getItemInfo(size_t x, size_t y)
{
    return field->getInfAboutItem(x, y);
}

std::string Game::getLandInfo(size_t x, size_t y)
{
    return field->getInfAboutLand(x, y);
}

size_t Game::getPlayersCount()
{
    return playersCount;
}

std::shared_ptr<GameParametersMemento> Game::createMemento()
{
    std::shared_ptr<GameParametersMemento> memento = std::make_shared<GameParametersMemento>();

    memento->playersCount = playersCount;
    memento->fieldParam = field->createMemento();

    for(const auto& curr : bases)
    {
        memento->baseNames.insert(std::pair(curr.first.toStdString(), Coords(curr.second.xCoord, curr.second.yCoord)));
    }

    return memento;
}

void Game::restoreMemento(std::shared_ptr<GameParametersMemento> memento)
{
    playersCount = memento->playersCount;
    for(const auto& curr : memento->baseNames)
    {
        bases.insert(std::pair(QString::fromUtf8(curr.first.c_str()), BaseInf(curr.second.x, curr.second.y)));
    }

    field->restoreMemento(memento->fieldParam);

    for(const auto& curr : memento->baseNames)
    {
        bases[QString::fromUtf8(curr.first.c_str())].base = field->getBaseByCoords(curr.second.x, curr.second.y);
    }
}
