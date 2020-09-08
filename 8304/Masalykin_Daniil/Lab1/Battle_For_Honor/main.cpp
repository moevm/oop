#include <iostream>
#include "Units/Unit.h"
#include "Battle Field/Field.h"
#include "Units/Swordsman.h"
#include "Units/Spearman.h"


int main()
{
    Field field;
    Unit spear = Spearman(5,5);
    field.print_field();
    field.insert_Unit(&spear);
    field.print_field();
    field.move_unit(&spear, 1, 1);
    Unit sword = Swordsman(5,5);
    field.insert_Unit(&sword);
    field.print_field();
    field.remove_Unit(&sword);
    field.print_field();

}
