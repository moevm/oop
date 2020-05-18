#include "Cell.h"
#include "AuxiliaryFunctionality/TextColoring.h"

#include <utility>

Cell::Cell() = default;

Cell::Cell(const Cell &cell) : unit(cell.unit->clone())
{
}

Cell::Cell(Cell &&cell) noexcept : unit(std::move(cell.unit)), base(std::move(cell.base))
{
    cell.unit = nullptr;
    cell.base = nullptr;
}

Cell& Cell::operator= (const Cell& cell)
{
    if (&cell == this)
        return *this;

    unit = cell.unit;
    return *this;
}

Cell& Cell::operator= (Cell&& cell) noexcept
{
    if (&cell == this)
        return *this;

    unit = std::move(cell.unit);

    return *this;
}

bool Cell::isUnitFree() const
{
    return unit == nullptr;
};

bool Cell::isBaseFree() const
{
    return base == nullptr;
}

void Cell::addUnit(std::shared_ptr<Unit> unit_)
{
    unit = std::move(unit_);
}

size_t Cell::delUnit()
{
    size_t deletingQuantity = unit->getUnitQuantity();
    unit = nullptr;
    return deletingQuantity;
}

void Cell::clearUnit()
{
    unit = nullptr;
}

void Cell::makeUnitSpeak()
{
    if(unit == nullptr)
    {
        throw CellException("Cell doesn't contain unit");
    }
    else
    {
        unit->describeYourself();
    }
}

void Cell::makeBaseSpeak()
{
    if(base == nullptr)
    {
        throw CellException("Cell doesn't contain base");
    }
    else
    {
        base->describeYourself();
    }
}

Cell::~Cell()
{
    unit  = nullptr;
    base = nullptr;
}

void Cell::addBase(std::shared_ptr<GameBase> base_)
{
    base = std::move(base_);
}

void Cell::giveUnitDamage(size_t damage)
{
    if(unit != nullptr)
    {
        unit->takeDamage(damage);
    }
    else
    {
        throw CellException("Attempt to attack an empty cell");
    }
}

std::string Cell::getInfAboutUnit()
{
    // FIXME: is it correct (externally) unit info
    std::string composite = unit->isComposite() != nullptr ? "C" : "Not c";
    return "It's " + composite + "omposite unit;" + unit->getUnitInf();
}

std::string Cell::getInfAboutBase()
{
    return base->getInformationAbout();
}

std::shared_ptr<GameBase> Cell::getBaseByCoords()
{
    return base;
}

std::shared_ptr<Unit> Cell::getUnitByCoords()
{
    return unit;
}
