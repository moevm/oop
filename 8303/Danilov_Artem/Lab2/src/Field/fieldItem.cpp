#include "fieldItem.h"

FieldItem::FieldItem ()
{
    land = new Desert();
}

FieldItem::FieldItem (const FieldItem& item) :
    unit(item.unit->itemCopy()),
    neutral(item.neutral),
    land(item.land) {}

FieldItem::FieldItem (FieldItem&& item) :
    unit(item.unit),
    neutral(item.neutral),
    land(item.land)   { }//

FieldItem::~FieldItem ()
{
    delUnit();
    delNeutral();
    delLandscape();
}

FieldItem &FieldItem::operator = (const FieldItem & item)
{
    if (&item == this)
        return *this;
    delUnit();
    delNeutral();
    delLandscape();
    unit = item.unit;
    neutral = item.neutral;
    land = item.land;
    delete item.unit;
    delete item.neutral;
    delete item.land;
    return *this;
}

FieldItem &FieldItem::operator = (FieldItem && item)
{
    if (&item == this)
        return *this;
    unit = item.unit;
    neutral = item.neutral;
    return *this;
}

void FieldItem::addUnit (Unit* item)
{
    unit = item;
//    unit = std::move(unit);
}

void FieldItem::delUnit ()
{
    delete unit;
    unit = nullptr;
}

void FieldItem::addNeutral (NeutralObj *item)
{
    neutral = item;
}

void FieldItem::delNeutral ()
{
    delete neutral;
    neutral = nullptr;
}

void FieldItem::setLandscape (Landscape *item)
{
    land = item;
}

void FieldItem::delLandscape ()
{
    delete land;
    land = nullptr;
}


bool FieldItem::isUnitFree () const
{
    return unit == nullptr;
}

Unit *FieldItem::getUnit () const
{
    return unit;
}

NeutralObj *FieldItem::getNeutral () const
{
    return neutral;
}

Landscape *FieldItem::getLandscape () const
{
    return land;
}

//std::string FieldItem::characteristics (unsigned int x, unsigned int y)
//{
//    return std::string();
//}
//
