#ifndef OOP_CELL_H
#define OOP_CELL_H

#include <memory>
#include "AuxiliaryFunctionality/Exceptions/fieldexception.h"

#include "Units/Unit.h"
#include "Landscape/Landscape.h"
#include "Bases/GameBase.h"

class Cell
{
public:
    Cell();
    ~Cell();
    Cell(const Cell& cell);
    Cell(Cell&& cell) noexcept;
    Cell& operator= (const Cell& cell);
    Cell& operator= (Cell&& cell) noexcept;

    [[nodiscard]] bool isUnitFree() const;
    [[nodiscard]] bool isBaseFree() const;
    void addUnit(std::shared_ptr<Unit> unit_);
    void addBase(std::shared_ptr<GameBase> base_);
    size_t delUnit();
    void giveUnitDamage(size_t damage);
    void clearUnit();
    void makeUnitSpeak();
    void makeBaseSpeak();
    std::string getInfAboutUnit();
    std::string getInfAboutBase();
    std::shared_ptr<GameBase> getBaseByCoords();
    std::shared_ptr<Unit> getUnitByCoords();

    Cell& operator* () { return *this; };

private:
    std::shared_ptr<Unit> unit{};
    std::shared_ptr<GameBase> base{};
};

#endif //OOP_CELL_H
