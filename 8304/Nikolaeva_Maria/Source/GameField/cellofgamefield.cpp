#include "cellofgamefield.h"


CellOfGameField::CellOfGameField()
{
    this->empty = true;
    neutralObject = new NoObject;
    unit = nullptr;
    landscape = new ProxyLandscape;
}


CellOfGameField::CellOfGameField(const CellOfGameField& cell)
{
    this->empty = cell.empty;
    this->unit = unit->clone();
    this->neutralObject = neutralObject->clone();
}


CellOfGameField& CellOfGameField::operator=(CellOfGameField& cell)
{
    if (this == &cell) {
        return *this;
    }

    this->empty = cell.empty;

    if (!cell.empty) {
        this->unit = cell.unit->clone();
        this->neutralObject = cell.neutralObject->clone();
    }

    return *this;
}


bool CellOfGameField::isEmpty()
{
    return this->empty;
}


void CellOfGameField::addUnit(Unit* unit)
{
    this->unit = unit;
    this->empty = false;

}


void CellOfGameField::deleteUnit()
{
    this->unit = nullptr;
    this->empty = true;
}


Unit* CellOfGameField::getUnit()
{
    return this->unit;
}


void CellOfGameField::addNeutralObject(NeutralObject *neutralObject)
{
    this->neutralObject = neutralObject;
}


void CellOfGameField::deleteNeutralObject()
{
    delete this->neutralObject;
    this->neutralObject = new NoObject;
}


NeutralObject* CellOfGameField::getNeutralObject()
{
    return this->neutralObject;
}


void CellOfGameField::addLandscape(Landscape *landscape)
{
    this->landscape = landscape;
}

void CellOfGameField::deleteLandscape()
{
    this->landscape = nullptr;
}


Landscape* CellOfGameField::getlandscape()
{
    return this->landscape;
}
