#include <QCoreApplication>
#include <iostream>
#include "facade.h"
#include "field.h"
#include "units.h"
#include "neutralobj.h"
#include "iterator.h"


int main()
{
    //Field* field = new Field(10, 10);
    //field->print_field();
    //LAB 1 TESTS

    /*Unit* unit1 = new HumanPlasmaTank(0, 1);
    Unit* unit2 = new HumanStormtrooper(0, 2);
    Unit* unit3 = new HumanDroid(0, 3);

    field->insert_Unit(unit1);
    field->insert_Unit(unit2);
    field->insert_Unit(unit3);

    field->create_ABase(8,1000);
    field->createAUnit('S');
    field->createAUnit('D');
    field->createAUnit('P');
    field->create_HBase(8,1000);
    field->createHUnit('S');
    field->createHUnit('D');
    field->createHUnit('P');
    field->print_field();

    Iterator iter(field);
    while(iter.canFindNext())
    {
        cout << (*iter)->getHealth() << "\n";
        iter.Next();
    }*/
    //Unit* unit = *iter;
    //std::cout << unit->getArmy() << " \n";

    /*field->print_field();
    field->move_Unit(unit1,1,2);
    field->print_field();
    field->remove_Unit(unit1);
    field->print_field();*/




    //LAB 2 TESTS
    /*field.create_Landscape();
    field.show_Landscape();

    field.create_Neutral(1,1,'M');
    field.create_Neutral(1,2,'V');
    field.create_Neutral(1,3,'W');
    field.create_Neutral(1,4,'A');
    field.show_Neutral();

    Base* base = field.create_ABase(8,1000);
    base->create_unit(&field,'S', 'H');
    base->create_unit(&field,'D', 'H');
    base->create_unit(&field,'P', 'H');
    base->create_unit(&field,'S', 'H');
    base->create_unit(&field,'L', 'H');
    field.print_field();

    FieldMine* mine = new FieldMine();
    Unit unit = HumanStormtrooper(0, 2);
    std::cout << unit.getHealth() << '\n';
    *mine >> &unit;
    std::cout << unit.getHealth() << '\n';*/
    //LAB 3 TESTS
    Facade* bivis = new Facade();
    bivis->start();

}
