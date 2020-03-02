#include <QCoreApplication>
#include "field.h"
#include "units.h"
#include "unist_types.h"

int main()
{
    Field field = Field(10, 10);
    HumanArmyFactory hu_army;
    AlienArmyFactory al_army;
    field.insert_Unit(hu_army.createStormtrooper(5,5));
    field.insert_Unit(al_army.createDroid(5,9));

    Unit unit1 = HumanPlasmaTank(0, 1);
    Unit unit2 = HumanStormtrooper(0, 2);
    Unit unit3 = HumanDroid(0, 3);

    field.insert_Unit(&unit1);
    field.insert_Unit(&unit2);
    field.insert_Unit(&unit3);

    field.print_field();
    field.move_Unit(&unit1,1,2);
    field.print_field();
    field.remove_Unit(&unit1);
    field.print_field();

    Field* newField = new Field(field);
    newField->print_field();
}
