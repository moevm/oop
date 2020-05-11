#include "concrete_units_classes.h"

AbsorbInfantry::AbsorbInfantry(Race race){
    health = new Attribute(100);
    armor = new Attribute(4);
    damage = new Attribute(20);
    this->race = race;
    absorbtionCoefficient = 0.3;
}

QString AbsorbInfantry::getClass() { return QString("AbsorbInfantry"); }

CritInfantry::CritInfantry(Race race){
    health = new Attribute(80);
    armor = new Attribute(2);
    damage = new Attribute(30);
    this->race = race;
    critFactor = 1.5;
}

QString CritInfantry::getClass() { return QString("CritInfantry"); }

AbsorbCavalry::AbsorbCavalry(Race race){
    health = new Attribute(150);
    armor = new Attribute(8);
    damage = new Attribute(25);
    this->race = race;
    absorbtionCoefficient = 0.2;
}

QString AbsorbCavalry::getClass() { return QString("AbsorbCavalry"); }

CritCavalry::CritCavalry(Race race){
    health = new Attribute(120);
    armor = new Attribute(3);
    damage = new Attribute(40);
    this->race = race;
    critFactor = 1.25;
}

QString CritCavalry::getClass() { return QString("CritCavalry"); }

AbsorbArcher::AbsorbArcher(Race race){
    health = new Attribute(80);
    armor = new Attribute(2);
    damage = new Attribute(20);
    this->race = race;
    absorbtionCoefficient = 0.1;
}

QString AbsorbArcher::getClass() { return QString("AbsorbArcher"); }

CritArcher::CritArcher(Race race){
    health = new Attribute(60);
    armor = new Attribute(2);
    damage = new Attribute(40);
    this->race = race;
    critFactor = 1.75;
}
QString CritArcher::getClass() { return QString("CritArcher"); }

