#include "base.h"
#include "arab_fabric.h"
#include "crusader_fabric.h"

std::map <int,Unit*> Units_ID = { {1, nullptr}, {2, nullptr}, {3, nullptr}, {4, nullptr}, {5, nullptr}, {6, nullptr}, {7, nullptr}, {8, nullptr}, {9, nullptr}, {10, nullptr}};


void Base::plus_unit()
{
    unit_now++;
}

void Base::minus_unit()
{
    unit_now--;
}

int Base::get_unit_now()
{
    return unit_now;
}

void Base::set_pos(int x_n, int y_n)
{
    x=x_n;
    y=y_n;
}

int Base::get_x()
{
    return x;
}

int Base::get_y()
{
    return y;
}

int Base::createCrusaderUnit( Warrior_ID id, int new_name, class Field *new_field, Base* new_base)
{
    int ret_id = 0;
    Fabrics* C_fabric = new Crusader_fabric();
    if (unitMax>unit_now)
    {
    plus_unit();
    Units_ID[num_id] = C_fabric->createWarrior(id, unit_now, new_field, new_base);
    //ret_id = num_id++;
    }
    else
    {
        std::cout << "Maximum unit count" << std::endl;
        Units_ID[num_id] = nullptr;
    }
    return unit_now;
}

Unit* Base::get_Unit(int id)
{
    return Units_ID[id];
}

void Base::delete_unit(int id)
{
    Units_ID[id]=nullptr;
}

void Base::clear_base()
{
    for (int i=1;i<unit_now+1;i++)
    {
        Units_ID[i] = nullptr;
    }
    unit_now=0;

}

int Base::createArabUnit( Warrior_ID id, int new_name, class Field *new_field, Base* new_base)
{
    int ret_id = 0;
    Fabrics* A_fabric = new Arab_fabric();
    if (unitMax>unit_now)
    {
    plus_unit();
    Units_ID[num_id] = A_fabric->createWarrior(id, unit_now, new_field, new_base);
    //ret_id = num_id++;
    }
    else
    {
        std::cout << "Maximum unit count" << std::endl;
        Units_ID[num_id] = nullptr;
    }
    return unit_now;
}


