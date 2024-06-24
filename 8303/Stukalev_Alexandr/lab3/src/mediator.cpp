#include "mediator.h"
#include "iostream"
Mediator::Mediator(Field* field)
{
    this->field = field;
}

void Mediator::attack(Unit* unit, int x, int y)
{
    if(field->getX() > x && field->getY() > y && x >= 0 && y >= 0)
    {
        if(field->checkABase(x,y))
        {
            Base* aBase = field->getABase();
            cout << "Health before: " << aBase->getHealth() << "\n";
            aBase->attackThis(unit->getDamage());
            cout << "Health after: " << aBase->getHealth() << "\n";
        }
        else if(field->checkHBase(x,y))
        {
            Base* hBase = field->getHBase();
            cout << "Health before: " << hBase->getHealth() << "\n";
            hBase->attackThis(unit->getDamage());
            cout << "Health after: " << hBase->getHealth() << "\n";
        }
        else if(field->checkUnit(x,y))
        {
            Unit* unitUnderFire = field->getUnit(x,y);
            cout << "Health before: " << unitUnderFire->getHealth() << "\n";
            unitUnderFire->attackThis(unit->getDamage());
            cout << "Health after: " << unitUnderFire->getHealth() << "\n";
            if(unitUnderFire->getHealth() <= 0)
            {
                field->remove_Unit(unitUnderFire);
            }
        }
    }
}
