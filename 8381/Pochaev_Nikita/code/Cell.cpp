#include "Cell.h"
#include "Auxiliary functionality/TextColoring.h"

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
        std::cout << ANSIColor::coloredString("Cell doesn't contain unit", ANSIColor::FG_RED) << std::endl;
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
        std::cout << ANSIColor::coloredString("Cell doesn't contain base", ANSIColor::FG_RED) << std::endl;
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
        throw std::out_of_range("Attempt to attack an empty cell");
    }
}
