#include "field.h"
#include "iostream"

Base::Base(int max_count, int health, int x, int y, string baseName):health(health),count(0),max_count(max_count), baseName(baseName)
{
    this->x = x;
    this->y = y;
    this->health= health;
    this->comp_unit = new Composit();
    LoggingProxy::logBaseCreate(this);
}

Base::Base(int max_count , int count, int health, int x, int y, string baseName):health(health),count(count),max_count(max_count), baseName(baseName)
{
    this->x = x;
    this->y = y;
    this->health= health;
    this->comp_unit = new Composit();
    LoggingProxy::logBaseCreate(this);
}

void Base::remove_unit(Unit* unit)
{
    //юнит удалить через observer
    LoggingProxy::logUnitRemove(unit);
    unit->removeObserver(this);
    comp_unit->remove_unit(unit);
    this->count--;
}
void Base::create_unit(Field* field,char name, char army)
{
    int x = 0, y = 0;
    bool check = false;
    if(army == 'H')
    {        
        if(!field->checkUnit(this->x+1, this->y))
        {
            check = true;
            x = this->x + 1;
            y = this->y;
        }
        if(!field->checkUnit(this->x, this->y + 1))
        {
            check = true;
            x = this->x;
            y = this->y + 1;
        }
        if(!field->checkUnit(this->x + 1, this->y + 1))
        {
            check = true;
             x = this->x + 1;
            y = this->y + 1;
        }
    }
    else if(army == 'A')
    {
        if(!field->checkUnit(this->x - 1, this->y))
        {
            check = true;
            x = this->x - 1;
            y = this->y;
        }
        if(!field->checkUnit(this->x, this->y - 1))
        {
            check = true;
            x = this->x;
            y = this->y - 1;
        }
        if(!field->checkUnit(this->x - 1, this->y - 1))
        {
            check = true;
            x = this->x - 1;
            y = this->y - 1;
        }
    }
    else
        return;
    if(this->count < this->max_count && check)
    {
        Unit* unit = nullptr;
        if(army == 'H')
        {
            field->allUnitsDis();
            if(name == 'S')
            {
                unit = hu_army.createStormtrooper(x,  y);
            }
            if(name == 'D')
            {
                unit = hu_army.createDroid(x,  y);
            }
            if(name == 'P')
            {
                unit = hu_army.createPlasmaTank(x,  y);
            }
        }
        else if(army == 'A')
        {
            field->allUnitsDis();
            if(name == 'S')
            {
                unit = al_army.createStormtrooper(x,  y);
            }
            if(name == 'D')
            {
                unit = al_army.createDroid(x,  y);
            }
            if(name == 'P')
            {
                unit = al_army.createPlasmaTank(x,  y);
            }
        }
        else
            return;
        if (unit == nullptr)
            return;
        LoggingProxy::logUnitCreate(unit);
        field->insert_Unit(unit);
        this->count++;
        unit->addObserver(this);
        comp_unit->add_unit(unit);
    }

}

void Base::insert_unit(Field *field, char name, char army, int health, int damage, int armor, int x, int y)
{
    Unit* unit = nullptr;
    if(army == 'H')
    {
        std::cout << '!';
        field->allUnitsDis();
        if(name == 'S')
        {
            unit = hu_army.createStormtrooper(x,  y);
        }
        if(name == 'D')
        {
            unit = hu_army.createDroid(x,  y);
        }
        if(name == 'P')
        {
            unit = hu_army.createPlasmaTank(x,  y);
        }
    }
    else if(army == 'A')
    {
        field->allUnitsDis();
        if(name == 'S')
        {
            unit = al_army.createStormtrooper(x,  y);
        }
        if(name == 'D')
        {
            unit = al_army.createDroid(x,  y);
        }
        if(name == 'P')
        {
            unit = al_army.createPlasmaTank(x,  y);
        }
    }
    unit->setHealth(health);
    unit->setDamage(damage);
    unit->setArmor(armor);
    field->insert_Unit(unit);
    this->count++;
    unit->addObserver(this);
    comp_unit->add_unit(unit);
}

void Base::update(Subject* subject)
{
    this->remove_unit(static_cast<Unit *>(subject));
}
bool Base::getIsMaxCount()
{
    if(this->count <= this->max_count)
        return true;
    return false;
}

void Base::move_unit(Field *field, char c, Unit* unit)
{
    if(c == 'w' && field->checkCell(unit->getX(),unit->getY() + 1))
    {
        field->move_Unit(unit,unit->getX(),unit->getY() + 1);
        LoggingProxy::logUnitMove(unit,unit->getX(),unit->getY() + 1);
    }
    else if(c == 'a' && field->checkCell(unit->getX() + 1,unit->getY()))
    {
        field->move_Unit(unit,unit->getX() + 1,unit->getY());
        LoggingProxy::logUnitMove(unit,unit->getX() + 1,unit->getY());
    }
    else if(c == 'd' && field->checkCell(unit->getX() - 1,unit->getY()))
    {
        field->move_Unit(unit,unit->getX() - 1,unit->getY());
        LoggingProxy::logUnitMove(unit,unit->getX() - 1,unit->getY());
    }
    else if(c == 's' && field->checkCell(unit->getX(),unit->getY() - 1))
    {
        field->move_Unit(unit,unit->getX(),unit->getY() - 1);
        LoggingProxy::logUnitMove(unit,unit->getX(),unit->getY() - 1);
    }
    else
        return;

}

int Base::getHealth()
{
    return this->health;
}

int Base::getMaxUnits()
{
    return this->max_count;
}

int Base::getCurrUnits()
{
    return this->count;
}

int Base::getX()
{
    return this->x;
}

int Base::getY()
{
    return this->y;
}

void Base::attackThis(int n)
{
    this->health -= n;
    if(this->health <= 0)
    {
        this->GameOver();
        return;
    }
    LoggingProxy::logBaseAttacked(this);
}

void Base::GameOver()
{
    LoggingProxy::logGameover(this);
    std::cout << "Game is over";
}

string Base::getBaseName()
{
    return baseName;
}
