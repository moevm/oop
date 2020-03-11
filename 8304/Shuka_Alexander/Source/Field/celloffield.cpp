#include "celloffield.h"


CellOfField::CellOfField()
{
    empty = true;
}


CellOfField::CellOfField(const CellOfField& cell)
{
    if (cell.unit) {
        this->unit = cell.unit->clone();
    }

    this->empty = cell.empty;
}


CellOfField::CellOfField(CellOfField&& cell)
{
    this->unit = std::move(cell.unit);
    this->empty = cell.empty;

    cell.empty = true;
}


CellOfField& CellOfField::operator=(const CellOfField& cell)
{
    if (this == &cell) {
        return *this;
    }

    this->unit.reset();

    if (!cell.isEmpty()) {
        this->unit = cell.unit->clone();
    }

    this->empty = cell.empty;

    return *this;
}


CellOfField& CellOfField::operator=(CellOfField&& cell)
{
    if (this == &cell) {
        return *this;
    }

    this->unit.reset();

    this->unit = std::move(cell.unit);
    this->empty = false;

    cell.empty = true;

    return *this;
}


void CellOfField::addUnit(std::shared_ptr<Unit> unit)
{
    this->unit = unit;
    this->empty = false;
}


void CellOfField::deleteUnit()
{
    if (this->unit) {
        this->unit.reset();
    }

    this->empty = true;
}


std::shared_ptr<Unit>& CellOfField::getUnit()
{
    return unit;
}


bool CellOfField::isEmpty() const
{
    return empty;
}
