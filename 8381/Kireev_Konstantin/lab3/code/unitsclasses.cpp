#include "unitsclasses.h"

AbsorbInfantry::AbsorbInfantry(unsigned int possessorId){
    health = new Feature(100);
    armor = new Feature(4);
    damage = new Feature(20);
    this->possessorId = possessorId;
    absorbtionCoefficient = 0.3;
}

QString AbsorbInfantry::getClass() { return QString("Пехота с ув. здоровьем"); }

CritInfantry::CritInfantry(unsigned int possessorId){
    health = new Feature(80);
    armor = new Feature(2);
    damage = new Feature(30);
    this->possessorId = possessorId;
    critFactor = 1.5;
}

QString CritInfantry::getClass() { return QString("Пехота с крит. уроном"); }

AbsorbCavalry::AbsorbCavalry(unsigned int possessorId){
    health = new Feature(150);
    armor = new Feature(8);
    damage = new Feature(25);
    this->possessorId = possessorId;
    absorbtionCoefficient = 0.2;
}

QString AbsorbCavalry::getClass() { return QString("Конница с ув. здоровьем"); }

CritCavalry::CritCavalry(unsigned int possessorId){
    health = new Feature(120);
    armor = new Feature(3);
    damage = new Feature(40);
    this->possessorId = possessorId;
    critFactor = 1.25;
}

QString CritCavalry::getClass() { return QString("Конница с крит. уроном"); }

AbsorbArcher::AbsorbArcher(unsigned int possessorId){
    health = new Feature(80);
    armor = new Feature(2);
    damage = new Feature(20);
    this->possessorId = possessorId;
    absorbtionCoefficient = 0.1;
}

QString AbsorbArcher::getClass() { return QString("Лучник с ув. здоровьем"); }

CritArcher::CritArcher(unsigned int possessorId){
    health = new Feature(60);
    armor = new Feature(2);
    damage = new Feature(40);
    this->possessorId = possessorId;
    critFactor = 1.75;
}
QString CritArcher::getClass() { return QString("Лучник с крит. уроном"); }

