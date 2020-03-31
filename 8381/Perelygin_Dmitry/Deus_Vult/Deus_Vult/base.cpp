#include "base.h"
#include "arab_fabric.h"
#include "crusader_fabric.h"

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




Unit* Base::createCrusaderUnit( Warrior_ID id, std::string new_name, class Field *new_field, Base* new_base)
{
    Fabrics* C_fabric = new Crusader_fabric();
    if (unitMax>unit_now)
    {
    plus_unit();
    return C_fabric->createWarrior(id, new_name, new_field, new_base);
    }
    else
    {
        std::cout << "Maximum unit count" << std::endl;
        return NULL;
    }
}

Unit* Base::createArabUnit( Warrior_ID id, std::string new_name, class Field *new_field, Base* new_base)
{
    Fabrics* A_fabric = new Arab_fabric();
    if (unitMax>unit_now)
    {
    plus_unit();
    return A_fabric->createWarrior(id, new_name, new_field, new_base);
    }
    else
    {
        std::cout << "Maximum unit count" << std::endl;
        return NULL;
    }
}


