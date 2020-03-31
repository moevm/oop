//
// Created by anton on 11.03.2020.
//

#include "Base.h"
#include "Fabric.h"
Base::Base(Field* tmpField, int x, int y, int maxNumber): field(tmpField), x(x), y(y), currentUnitNumber(0), maxNumberUnits(maxNumber), health(100){}

void Base::createUnit(char type) {

    if(currentUnitNumber == maxNumberUnits)
    {
        puts("can't create any more.");
        return;
    }
    Unit* newUnit = nullptr;
    switch (type)
    {
        case 'b':
            newUnit = ThiefFabric().createSecondType();
            break;
        case 'd':
            newUnit =  WarriorFabric().createFirstType();
            break;
        case 'e':
            newUnit = ThiefFabric().createFirstType();
            break;
        case 'f':
            newUnit = WizardFabric().createFirstType();
            break;
        case 'n':
            newUnit = WizardFabric().createSecondType();
            break;
        case 'p':
            newUnit = WarriorFabric().createSecondType();
            break;
        default:
            return;
    }

    if(field->addUnit(newUnit, this->x + 1, this->y )){}
    else if(field->addUnit(newUnit, this->x + 1, this->y + 1)){}
    else if(field->addUnit(newUnit, this->x , this->y + 1)){}
    else if(field->addUnit(newUnit, this->x - 1, this->y + 1)){}
    else if(field->addUnit(newUnit, this->x, this->y)){}
    else if(field->addUnit(newUnit, this->x - 1, this->y - 1)){}
    else if(field->addUnit(newUnit, this->x, this->y - 1)){}
    else if(field->addUnit(newUnit, this->x + 1, this->y - 1)){
        delete newUnit;
        return;
    }
    newUnit->addObserver(this);
    currentUnitNumber++;
    unitsList.push_back(newUnit);
}

void Base::deleteUnit(Unit * tmp) {
    field->deleteUnit(tmp);
    for(auto iter = unitsList.begin(); iter != unitsList.end(); iter++)
        if(*iter == tmp) {
            unitsList.erase(iter);
            break;
        }
    tmp->deleteObserver(this);
    currentUnitNumber--;
}

void Base::update(Subject* subject)
{
    deleteUnit(static_cast<Unit*>(subject));
}