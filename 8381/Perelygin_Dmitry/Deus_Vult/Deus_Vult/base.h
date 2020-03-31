#ifndef BASE_H
#define BASE_H
#include <iostream>

class Unit;

enum Warrior_ID { Infantryman_ID=0, Archer_ID=1, Horseman_ID=2};
// Иерархия классов игровых персонажей

class Base
{

protected:
    int HP;
    int unitMax;
    int unit_now;

public:
    Base()
    {
        HP = 300;
        unitMax = 10;
        unit_now = 0;
    }

    void plus_unit();

    void minus_unit();

    int get_unit_now();

    Unit* createCrusaderUnit(Warrior_ID id, std::string new_name, class Field *new_field, Base* new_base);

    Unit* createArabUnit( Warrior_ID id, std::string new_name, class Field *new_field, Base* new_base);
};

#endif // BASE_H
