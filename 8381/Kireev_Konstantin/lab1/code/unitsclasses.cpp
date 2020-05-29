#include "unitsclasses.h"

DamageAbsorberInfantry::DamageAbsorberInfantry()
{
    health = 90;
    armor = 4;
    damage = 23;
    absorptionFactor = 0.3;
}

QString DamageAbsorberInfantry::getClass()
{
    return QString("DmgAInf");
}


CritInfantry::CritInfantry()
{
    health = 100;
    armor = 4;
    damage = 20;
    critFactor = 1.5;
}

QString CritInfantry::getClass()
{
    return QString("CritInf");
}


DamageAbsorberCavalry::DamageAbsorberCavalry()
{
    health = 120;
    armor = 6;
    damage = 40;
    absorptionFactor = 0.2;
}

QString DamageAbsorberCavalry::getClass()
{
    return QString("DmgACav");
}


CritCavalry::CritCavalry()
{
    health = 150;
    armor = 6;
    damage = 30;
    critFactor = 1.25;
}

QString CritCavalry::getClass()
{
    return QString("CritCav");
}


DamageAbsorberArcher::DamageAbsorberArcher()
{
    health = 60;
    armor = 2;
    damage = 35;
    absorptionFactor = 0.1;
}

QString DamageAbsorberArcher::getClass()
{
    return QString("DmgAArc");
}


CritArcher::CritArcher()
{
    health = 80;
    armor = 2;
    damage = 20;
    critFactor = 1.75;
}

QString CritArcher::getClass()
{
    return QString("CritArc");
}
