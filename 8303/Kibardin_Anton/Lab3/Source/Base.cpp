//
// Created by anton on 11.03.2020.
//

#include "Base.h"
#include "Fabric.h"
Base::Base(Field* tmpField, int x, int y, int maxNumber, int number): field(tmpField), x(x), y(y), currentUnitNumber(0), maxNumberUnits(maxNumber), health(100), baseNumber(number){}

void Base::createUnit(char type, std::string unitName) {

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

    if(field->addUnit(newUnit, this->x + 1, this->y )){ newUnit->setX(this->x+1); newUnit->setY(this->y);}
    else if(field->addUnit(newUnit, this->x + 1, this->y + 1)){ newUnit->setX(this->x+1); newUnit->setY(this->y+1);}
    else if(field->addUnit(newUnit, this->x , this->y + 1)){ newUnit->setX(this->x); newUnit->setY(this->y+1);}
    else if(field->addUnit(newUnit, this->x - 1, this->y + 1)){ newUnit->setX(this->x-1); newUnit->setY(this->y+1);}
    else if(field->addUnit(newUnit, this->x, this->y)){ newUnit->setX(this->x); newUnit->setY(this->y);}
    else if(field->addUnit(newUnit, this->x - 1, this->y - 1)){ newUnit->setX(this->x-1); newUnit->setY(this->y-1);}
    else if(field->addUnit(newUnit, this->x, this->y - 1)){ newUnit->setX(this->x); newUnit->setY(this->y-1);}
    else if(field->addUnit(newUnit, this->x + 1, this->y - 1)){ newUnit->setX(this->x+1); newUnit->setY(this->y-1);}
    else{
        delete newUnit;
        return;
    }
    newUnit->setName(unitName);
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

void Base::getDamage(int attackPower)
{
    health -= attackPower;
    if(health <= 0)
    {
        for(auto iter : unitsList)
        {
            iter->death();
        }
    }
    field->deleteBase(this);
}

int Base::getNumber() const{
    return baseNumber;
}

void Base::printStatus() const {
    std::cout << "base number: " << baseNumber << std::endl;
    std::cout << "health: " << health << std::endl;
    std::cout << "position: " << x << ", " << y << std::endl;
    std::cout << "max number units: " << maxNumberUnits << std::endl;
    std::cout << "current units number: " << currentUnitNumber << std::endl;
    std::cout << "Units:" << std::endl;
    for(auto iter : unitsList)
    {
        std::cout << (*iter);
    }
    puts("------------------");
}