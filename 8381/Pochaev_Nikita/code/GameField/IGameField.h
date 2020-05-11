#ifndef OOP_IGAMEFIELD_H
#define OOP_IGAMEFIELD_H

#include <utility>

#include "InformationHeaders/constPar.h"
#include "AuxiliaryFunctionality/Array2D.h"
#include "AuxiliaryFunctionality/GameFieldIterator.h"
#include "Units/ObjectFactory.h"
#include "Cell.h"

class IGameField
{
public:
    [[nodiscard]] virtual size_t getWidth() const = 0;
    [[nodiscard]] virtual size_t getHeight() const = 0;

    virtual void addUnit(const std::shared_ptr<Unit> &unit, size_t x, size_t y) = 0;
    virtual void addBase(const std::shared_ptr<GameBase> &base, size_t x, size_t y) = 0;
    virtual void delUnit(size_t x, size_t y) = 0;
    virtual bool isCellFreeForUnit(size_t x, size_t y) = 0;
    virtual bool isCellFreeForBase(size_t x, size_t y) = 0;
    virtual void informationAboutCell(size_t x, size_t y) = 0;
    virtual std::shared_ptr<GameBase> getBaseByCoords(size_t x, size_t y) = 0;
    virtual std::shared_ptr<Unit> getUnitByCoords(size_t x, size_t y) = 0;

    virtual void moveUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y) = 0;
    virtual void moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDest) = 0;
    virtual void meleeAttackUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y) = 0;
    virtual void meleeAttackUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDist) = 0;

    virtual void getTotalInformation() = 0;
    virtual std::string getInfAboutBase(size_t xDest, size_t yDest) = 0;
    virtual std::string getInfAboutUnit(size_t xDest, size_t yDest) = 0;
};


#endif //OOP_IGAMEFIELD_H
