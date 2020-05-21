//
// Created by Artem Butko on 15/05/2020.
//

#include "Base.h"

Base::Base(Field *field, int x, int y, int unitLimit)
{
    this->field = field;
    this->x = x;
    this->y = y;
    this->unitLimit = unitLimit;
    this->unitCount = 0;
    this->unitDead = 0;
    this->health.set(1000);
    this->damage.set(60, 2, 0);
    this->id = 'B';
    unitsOnBase['M'] = 0;
    unitsOnBase['W'] = 0;
    unitsOnBase['A'] = 0;
    unitsOnBase['C'] = 0;
    unitsOnBase['K'] = 0;
    unitsOnBase['S'] = 0;
}

int Base::createUnit(char id)
{
    const auto found = unitsOnBase.find(id);
    if(found == unitsOnBase.cend())
    {
        std::cout << "ERROR: wrong ID!" << std::endl;
        return 1;
    }
    else if (unitCount >= unitLimit)
    {
        std::cout << "ERROR: unit limit!" << std::endl;
        return 1;
    }
    else
    {
        unitsOnBase[id] += 1;
        unitCount++;
    }
    return 0;
}

void Base::getInformation()
{
    std::cout <<  "=========== BASE INFORMATION ==========" << std::endl;
    std::cout <<  "HEALTH: " << this->health.get() << std::endl;
    std::cout <<  "DAMAGE: " << this->damage.getDamage() << std::endl;
    std::cout <<  "------------ UNITS ON BASE ------------" << std::endl;
    std::cout <<  "MAGES                                " << unitsOnBase['M']
              <<  "\nWIZARDS                              " << unitsOnBase['W']
              <<  "\nARCHERS                              " << unitsOnBase['A']
              <<  "\nCROSSBOWMANS                         " << unitsOnBase['C']
              <<  "\nKNIGHTS                              " << unitsOnBase['K']
              <<  "\nSPEARMANS                            " << unitsOnBase['S']
              <<  "\nTOTAL:                               " << unitCount <<
                  "\nLIMIT:                               " << unitLimit <<
                  "\n------------ UNITS ON FIELD -----------" << std::endl;
    unitsOnField.getInformation();
    std::cout << "\nDEAD:                                " << unitDead <<
                  "\n======================================="
                  << std::endl;
    std::cout << std::endl;
}

IUnit* Base::getUnit(char id)
{
    const auto found = unitsOnBase.find(id);
    if(found == unitsOnBase.cend())
    {
        std::cout << "ERROR: wrong ID!" << std::endl;
        return nullptr;
    }
    else if(unitsOnBase[id] == 0)
    {
        std::cout << "ERROR: unit isn't on base!" << std::endl;
        return nullptr;
    }
    else
    {
        unitsOnBase[id]--;
        unitCount--;
        IUnit* unit;
        switch (id)
        {
            case 'M':
                unit = unitFactory.createMage();
                break;
            case 'W':
                unit = unitFactory.createWizard();
                break;
            case 'A':
                unit = unitFactory.createArcher();
                break;
            case 'C':
                unit = unitFactory.createCrossbowman();
                break;
            case 'K':
                unit = unitFactory.createKnight();
                break;
            case 'S':
                unit = unitFactory.createSpearman();
                break;
            default:
                std::cout << "ERROR: wrong unit id!" << std::endl;
                return nullptr;
        }
        unitsOnField.addUnit(unit);
        unit->addFollower(this);
        return unit;
    }
}

void Base::update(Subject* subject)
{
    auto* unit = static_cast<Object*>(subject);
    unitsOnField.deleteUnit(unit);
    this->unitDead++;
}
