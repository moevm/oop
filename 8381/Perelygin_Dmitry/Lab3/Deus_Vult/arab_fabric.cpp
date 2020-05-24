#include "arab_fabric.h"


// Реализация параметризированного фабричного метода
Unit* Arab_fabric::createWarrior( Warrior_ID id, int  new_name, class Field *new_field, Base* new_base )
{
    Unit * p = nullptr;
    switch (id)
    {
        case Infantryman_ID:
            p = new Arab(new_name,new_field, new_base);
            break;
        case Archer_ID:
            p = new ArabArcher(new_name,new_field, new_base);
            break;
        case Horseman_ID:
            p = new CamelRider(new_name,new_field, new_base);
            break;
    }
    return p;
};
