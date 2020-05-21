#include "GameField.h"

#include <cmath>
#include <iostream>

#include "Units/Creatures/Peasant.h"
#include "Units/Creatures/Heck.h"
#include "Units/Creatures/Swordsman.h"
#include "Units/Creatures/Ifrit.h"
#include "Units/Creatures/Archer.h"
#include "Units/Creatures/Succubus.h"
#include "Units/Creatures/Magician.h"
#include "Units/Creatures/Demon.h"
#include "Units/Creatures/Knight.h"
#include "Units/Creatures/Cerberus.h"
#include "AuxiliaryFunctionality/TextColoring.h"
#include "Landscape/Champaign.h"

GameField::GameField(size_t width_, size_t height_) :
    cellMatrix(width_, height_), unitsCount{},
    width(width_), height(height_)
{
    maxUnitsCount = width_ * height_;
}

GameField::GameField(const GameField &field) :
    cellMatrix(field.cellMatrix), unitsCount(field.unitsCount),
    maxUnitsCount(field.maxUnitsCount), baseCount(field.baseCount)
{
}

GameField::GameField(GameField &&field) noexcept :
        cellMatrix(std::move(field.cellMatrix)), unitsCount(field.unitsCount),
        maxUnitsCount(field.maxUnitsCount), baseCount(field.baseCount)
{
}

GameField& GameField::operator= (const GameField &field)
{
    if(&field == this)
        return *this;

    cellMatrix = field.cellMatrix;
    maxUnitsCount = field.maxUnitsCount;
    unitsCount = field.unitsCount;

    return *this;
}

GameField& GameField::operator= (GameField &&field) noexcept
{
    if(&field == this)
        return *this;

    cellMatrix = field.cellMatrix;
    maxUnitsCount = field.maxUnitsCount;
    unitsCount = field.unitsCount;

    return *this;
}

void GameField::addUnit(const std::shared_ptr<Unit>& unit, size_t x, size_t y)
{
    if(unitsCount + unit->getUnitQuantity() > maxUnitsCount)
    {
        throw SimpleFieldException("fields units limit reached");
    }
    else if(x > cellMatrix.getWidth() || y > cellMatrix.getHeight())
    {
        throw CoordsNotPartOfTheField(x, y, getWidth(), getHeight());
    }
    else if(cellMatrix[x][y]->isUnitFree())
    {
        cellMatrix[x][y]->addUnit(unit);
        unit->registerObserver(shared_from_this());
        if(unit->isComposite())
        {
            unitsCount += unit->getUnitQuantity();
        }
        else
        {
            unitsCount++;
        }
        unit->reallocation(x, y);
        return;
    }
    else
    {
        throw FieldBusyCellException(x, y);
    }
}

/**
 * We can't add base on cell where already there is unit, but next we can add unit
 * on cell there already is base
 * @param x
 * @param y
 * @return
 */
void GameField::addBase(const std::shared_ptr<GameBase> &base, size_t x, size_t y)
{
    // TODO: проверки на ландшафт
    if(baseCount >= maxBaseCount)
    {
        throw SimpleFieldException("fields bases limit reached");
    }
    else if(x + 1 > cellMatrix.getWidth() || y + 1 > cellMatrix.getHeight())
    {
        throw CoordsNotPartOfTheField(x, y, getWidth(), getHeight());
    }
    else if(cellMatrix[x][y]->isUnitFree() && cellMatrix[x][y]->isBaseFree())
    {
        cellMatrix[x][y]->addBase(base);
        baseCount++;
    }
}

void GameField::delUnit(size_t x, size_t y)
{
    if(!cellMatrix[x][y]->isUnitFree())
        unitsCount -= cellMatrix[x][y]->delUnit();
}

bool GameField::isCellFreeForUnit(size_t x, size_t y)
{
    return cellMatrix[x][y]->isUnitFree();
}

bool GameField::isCellFreeForBase(size_t x, size_t y)
{
    return  cellMatrix[x][y]->isBaseFree();
}

void GameField::informationAboutCell(size_t x, size_t y)
{
    if(isCellFreeForUnit(x, y) && isCellFreeForBase(x, y))
    {
        std::cout << "I'm Cell and I'm empty as your life" << std::endl;
        return;
    }
    else if (!isCellFreeForBase(x, y))
    {
        cellMatrix[x][y]->makeBaseSpeak();
    }
    if(!isCellFreeForUnit(x, y))
    {
        cellMatrix[x][y]->makeUnitSpeak();
    }
    else
    {
        std::cout << "There's no unit on cell" << std::endl;
    }
}

// function-style cast
GameField::iterator GameField::begin()
{
    return iterator(cellMatrix[0][0]);
}

GameField::iterator GameField::end()
{
    return iterator(cellMatrix[cellMatrix.getWidth()][cellMatrix.getHeight()]);
}

GameField::const_iterator GameField::begin() const
{
    return const_iterator(cellMatrix[0][0]);
}

GameField::const_iterator GameField::end() const
{
    return const_iterator(cellMatrix[cellMatrix.getWidth()][cellMatrix.getHeight()]);
}

void GameField::moveUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y)
{
    if(cellMatrix.getHeight() >= y && cellMatrix.getWidth() >= x)
    {
        if (cellMatrix[x][y]->isUnitFree())
        {
            int dist_x = abs(static_cast<int>(sender->getCoords().x) - static_cast<int>(x));
            int dist_y = abs(static_cast<int>(sender->getCoords().y) - static_cast<int>(y));
            if (dist_x <= static_cast<int>(x + sender->getMovementRange()) && dist_y <= static_cast<int>(y + sender->getMovementRange()))
            {
                cellMatrix[x][y]->addUnit(sender);
                Coords old_coords = sender->getCoords();
                sender->reallocation(x, y);
                clearUnitByCoords(old_coords);
                sender = nullptr;
                return;
            }
            else
            {
                throw std::invalid_argument("Too long distance for current Unit");
            }
        }
        else
        {
            throw FieldBusyCellException(x, y);
        }
    }
    else
    {
        throw CoordsNotPartOfTheField(x, y, getWidth(), getHeight());
    }
}

void GameField::clearUnitByCoords(Coords oldCoords)
{
    cellMatrix[oldCoords.x][oldCoords.y]->clearUnit();
}

void GameField::getTotalInformation()
{
    std::cout << ANSIColor::coloredString("Current field status:", ANSIColor::FG_BLUE) << std::endl;
    std::cout << "Maximum number of units on field: " <<  maxUnitsCount << std::endl;
    std::cout << "Current number of units on the field: " << unitsCount << std::endl;
    std::cout << "Current number of bases on the field: " << baseCount << std::endl;
}

void GameField::updateAfterDeath(std::shared_ptr<Unit> corpse, size_t x, size_t y)
{
    unitsCount -= corpse->getUnitQuantity();
    cellMatrix[x][y]->delUnit();
}

size_t GameField::getWidth() const
{
    return width;
}

size_t GameField::getHeight() const
{
    return height;
}

void GameField::meleeAttackUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y)
{
    if(cellMatrix.getHeight() >= y && cellMatrix.getWidth() >= x)
    {
        int dist_x = abs(static_cast<int>(sender->getCoords().x) - static_cast<int>(x));
        int dist_y = abs(static_cast<int>(sender->getCoords().y) - static_cast<int>(y));
        if (dist_x <= static_cast<int>(x + (sender->getMovementRange()) && dist_y <= static_cast<int>(y + sender->getMovementRange())))
        {
            cellMatrix[x][y]->giveUnitDamage(sender->getMeleeAttackStrength());
            return;
        }
        else
        {
            throw std::invalid_argument("Too long distance for current Unit");
        }
    }
    else
    {
        throw CoordsNotPartOfTheField(x, y, getWidth(), getHeight());
    }
}

void GameField::meleeAttackUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDest)
{
    std::shared_ptr<Unit> tempUnit = cellMatrix[xSource][ySource]->getUnitByCoords();
    meleeAttackUnit(tempUnit, xDest, yDest);
}

size_t GameField::thatIsOnCell(size_t x, size_t y, std::vector<eRequest> items)
{
    size_t itemsCount{};
    if(cellMatrix[x][y]->isUnitFree())
    {
        itemsCount++;
        items.push_back(UNIT_INFO);
    }
    if(cellMatrix[x][y]->isBaseFree())
    {
        itemsCount++;
        items.push_back(BASE_INFO);
    }

    return itemsCount;
}

std::shared_ptr<GameBase> GameField::getBaseByCoords(size_t x, size_t y)
{
    return cellMatrix[x][y]->getBaseByCoords();
}

std::shared_ptr<Unit> GameField::getUnitByCoords(size_t x, size_t y)
{
    return cellMatrix[x][y]->getUnitByCoords();
}

void GameField::moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDest)
{
    std::shared_ptr<Unit> tempUnit = cellMatrix[xSource][ySource]->getUnitByCoords();
    moveUnit(tempUnit, xDest, yDest);
}

std::string GameField::getInfAboutBase(size_t xDest, size_t yDest)
{
    return cellMatrix[xDest][yDest]->getBaseByCoords()->getInformationAbout();
}

std::string GameField::getInfAboutUnit(size_t xDest, size_t yDest)
{
    return cellMatrix[xDest][yDest]->getUnitByCoords()->getUnitInf();
}

std::shared_ptr<FieldParametersMemento> GameField::createMemento()
{
    std::shared_ptr<FieldParametersMemento> memento = std::make_shared<FieldParametersMemento>();
    memento->unitsCount = unitsCount;
    memento->maxUnitsCount = maxUnitsCount;
    memento->baseCount = baseCount;
    memento->maxBaseCount = maxBaseCount;
    memento->width = width;
    memento->height = height;

    for(size_t i = 0; i < cellMatrix.getWidth(); ++i)
    {
        for(size_t j = 0; j < cellMatrix.getHeight(); ++j)
        {
            if(!cellMatrix[i][j]->isBaseFree())
            {
                memento->bases.insert(std::pair(Coords(i, j), cellMatrix[i][j]->getBaseByCoords()->createMemento()));
            }
            if(!cellMatrix[i][j]->isUnitFree())
            {
                memento->units.insert(std::pair(Coords(i, j), cellMatrix[i][j]->getUnitByCoords()->createMemento()));
            }
        }
    }

    return memento;
}

void GameField::restoreMemento(std::shared_ptr<FieldParametersMemento> memento)
{
    unitsCount = memento->unitsCount;
    maxUnitsCount = memento->maxUnitsCount;
    baseCount = memento->maxUnitsCount;
    maxBaseCount = memento->maxBaseCount;
    width = memento->width;
    height = memento->height;

    BaseMaster master;
    HellBaseBuilder hellBaseBuilder;
    HumanBaseBuilder humanBaseBuilder;
    std::map<Coords, std::shared_ptr<BaseParametersCaretaker>>::iterator basesIter;
    for(basesIter = memento->bases.begin(); basesIter != memento->bases.end(); ++basesIter)
    {
        size_t x = basesIter->first.x;
        size_t y = basesIter->first.y;
        switch(basesIter->second->type)
        {
            case HELL_BASE:
                master.setBaseBuilder(&hellBaseBuilder);
                break;
            case HUMAN_BASE:
                master.setBaseBuilder(&humanBaseBuilder);
            case NONE_BASE:
                return;
        }
        master.constructBase();
        cellMatrix[x][y]->addBase(master.getBase());
        cellMatrix[x][y]->getBaseByCoords()->restoreMemento(basesIter->second);
    }

    std::map<Coords, std::shared_ptr<UnitParametersMemento>>::iterator unitIter;
    for(unitIter = memento->units.begin(); unitIter != memento->units.end(); ++unitIter)
    {
        size_t x = unitIter->first.x;
        size_t y = unitIter->first.y;
        eUnitsType type = unitIter->second->type;
        std::shared_ptr<Unit> restUnit = cellMatrix[unitIter->second->creationBaseCoords.x][unitIter->second->creationBaseCoords.y]->getBaseByCoords()->getUnit(type);
        restUnit->restoreMemento(unitIter->second);
        addUnit(restUnit, x, y);
    }
}
