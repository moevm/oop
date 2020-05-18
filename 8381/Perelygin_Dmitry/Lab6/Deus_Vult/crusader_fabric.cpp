#include "crusader_fabric.h"


// Реализация параметризированного фабричного метода
Unit* Crusader_fabric::createWarrior ( Warrior_ID id, int new_name, class Field *new_field, Base* new_base )
{
    Unit * p = nullptr;

        switch (id)
        {
            case Infantryman_ID:
                p = new Crusader(new_name,new_field, new_base);
                break;
            case Archer_ID:
                p = new CrusaderArcher(new_name,new_field, new_base);
                break;
            case Horseman_ID:
                p = new Knight(new_name,new_field, new_base);
                break;
          }
    return p;
};


