#include <iostream>
#include "Unit/Unit.h"
#include "Field.h"
#include "Unit/UnitCreater.h"

#include "Unit/Tank.h"
#include "Unit/ArmoredCar.h"
#include "Unit/Rifleman.h"

#include "Base.h"
#include "iterator.h"
#include "unitsgroup.h"
#include "facade.h"

/*
void exec1(){

    Field* field= new Field(7, 7, 10);

    Unit *tank = new Tank(2, 2);
    Unit *armoredCar = new ArmoredCar(3, 3);
    Unit *rifleman = new Rifleman(3, 5);
    Unit *rifleman2 = new Rifleman(4, 5);

    UnitsGroup *group = new UnitsGroup;
    group->addUnit(rifleman);
    group->addUnit(tank);
    group->addUnit(rifleman2);

    std::cout << "Group of riflemen's" << std::endl;
    group->print();

    field->addUnit(tank);
    field->addUnit(armoredCar);
    field->addUnit(rifleman);
    field->print();

//    field->moveUnit(tank, tank->getx(), tank->gety()+1);
//    field->moveUnit(armoredCar, armoredCar->getx(), armoredCar->gety()+1);
//    field->moveUnit(rifleman, rifleman->getx()-1, rifleman->gety());
//    field->removeUnit(rifleman);
//    field->print();

    std::cout << "Create base" << std::endl;
    Base *base = field->createBase(2,3, 5, 100);
    Unit* car2 = base->createUnit('C');
    Unit* tank2 = base->createUnit('T');
   Unit* medic2 = base->createUnit('M');
    Unit* sniper2 = base->createUnit('S');

    field->print();
    field->getBase()->printInfo();

    base->exitBase(car2);
    base->exitBase(medic2);

    field->print();
    field->getBase()->printInfo();

    car2->death();

    field->print();
    field->getBase()->printInfo();

    std::cout << "3 ---------------------------"<< std::endl;

    std::cout << "Armors using iterator: " << std::endl;
    Iterator iter1(*field);

    while (iter1.goNext()){
        Unit *u = *iter1;
        u->print();
        std::cout << " " << u->param.armor << std::endl;
    }
    std::cout << "The end!" << std::endl;
} */

void exec2(){
    Facade *facade = new Facade();
    facade->createField();
    facade->play();
}

//-------------------------------
int main() {

    exec2();

    return 0;
}
