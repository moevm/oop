#include "armor.h"

GetArmor::GetArmor(Armor* a) : armor(a)
{

}

void GetArmor::operator +=(Unit &unit)
{
    armor->use(unit);
}
string GetArmor::getType()const{
    return "neutral";
}

NeutralType GetArmor::getTypeEnum()
{
    return armor->type();
}
GetArmor::~GetArmor()
{
    delete armor;
}


string GetArmor::characteristic()
{
    return "GetArmor";
}

void Visor::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+20);
}

NeutralType Visor::type()
{
    return VISOR;
}

void Lat::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+40);
}

NeutralType Lat::type()
{
    return LAT;
}

void Boots::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+60);
}

NeutralType Boots::type()
{
    return BOOTS;
}



