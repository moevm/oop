#include "field.h"

Base::Base(int max_count, int health):health(1000),x(0),y(0),count(0),max_count(max_count)
{
    this->health= health;
    this->comp_unit = new Composit();
}

void Base::remove_unit(Unit* unit)
{
    //юнит удалить через observer
    unit->removeObserver(this);
    comp_unit->remove_unit(unit);
    this->count--;
}
void Base::create_unit(Field* field,char name, char army)
{
    int x = 0, y = 0;
    bool check = false;
    if(field->field[this->y][this->x + 1].is_full == false)
    {
        check = true;
        x = this->x + 1;
        y = this->y;
    }
    if(field->field[this->y + 1][this->x].is_full == false)
    {
        check = true;
        x = this->x;
        y = this->y + 1;
    }
    if(field->field[this->y + 1][this->x + 1].is_full == false)
    {
        check = true;
        x = this->x + 1;
        y = this->y + 1;
    }
    if(this->count < this->max_count && check)
    {
        Unit* unit = nullptr;
        if(army == 'H')
        {
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
        field->insert_Unit(unit);
        this->count++;
        unit->removeObserver(this);
        comp_unit->add_unit(unit);
    }

}

void Base::update(Subject* subject)
{
    this->remove_unit(static_cast<Unit *>(subject));
}
