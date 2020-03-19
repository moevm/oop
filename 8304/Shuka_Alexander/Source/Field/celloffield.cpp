#include "celloffield.h"

using namespace unit;


CellOfField::CellOfField()
{
    empty = true;
    NoObjectFactory factory;
    this->neutralObject = factory.createObject();
    this->landscape = std::shared_ptr<ProxyLandscape>(new ProxyLandscape);
}


CellOfField::CellOfField(const CellOfField& cell)
{
    doCopy(cell);
}


CellOfField::CellOfField(CellOfField&& cell)
{
    doMove(cell);
}


CellOfField& CellOfField::operator=(const CellOfField& cell)
{
    if (this == &cell) {
        return *this;
    }

    doCopy(cell);

    return *this;
}


CellOfField& CellOfField::operator=(CellOfField&& cell)
{
    if (this == &cell) {
        return *this;
    }

    doMove(cell);

    return *this;
}


void CellOfField::addUnit(std::shared_ptr<Unit> unit)
{
    this->unit = unit;

    if (unit) {
        this->empty = false;
    }
}


void CellOfField::deleteUnit()
{
    this->unit = nullptr;
    this->empty = true;
}


std::shared_ptr<Unit> CellOfField::getUnit() const
{
    return unit;
}


bool CellOfField::isEmpty() const
{
    return empty;
}


void CellOfField::setNeutralObject(std::shared_ptr<NeutralObject> neutralObject)
{
    this->neutralObject = std::move(neutralObject);
}


std::shared_ptr<NeutralObject> CellOfField::getNeutralObject() const
{
    return neutralObject;
}


void CellOfField::deleteNeutralObject()
{
    NoObjectFactory factory;
    this->neutralObject = factory.createObject();
}


void CellOfField::setLandscape(std::shared_ptr<Landscape> landscape)
{
    this->landscape = std::move(landscape);
}


std::shared_ptr<Landscape> CellOfField::getLandscape() const
{
    return landscape;
}


void CellOfField::doCopy(const CellOfField& cell)
{
    if (cell.landscape) {
        this->landscape = cell.landscape->clone();
    }

    if (cell.neutralObject) {
        this->neutralObject = cell.neutralObject->clone();
    }

    this->unit = nullptr;
    this->empty = cell.empty;

    if (!cell.isEmpty()) {
        this->unit = cell.unit->clone();
    }
}


void CellOfField::doMove(CellOfField& cell)
{
    this->unit = nullptr;
    this->landscape = std::move(cell.landscape);
    this->neutralObject = std::move(cell.neutralObject);
    this->unit = std::move(cell.unit);
    this->empty = cell.empty;
    cell.empty = true;
}
