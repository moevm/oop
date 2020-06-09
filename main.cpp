#include <iostream>
#include "Unit/Unit.h"
#include "Field.h"
#include "Unit/UnitCreater.h"

#include "Unit/Tank.h"
#include "Unit/ArmoredCar.h"
#include "Unit/Rifleman.h"
#include "Neutral/damage.h"

#include "Base.h"
//-------------------------------

void example1(){
    Field* field= new Field(7, 7, 10);

    Unit *tank = new Tank(2, 2);
    Unit *armoredCar = new ArmoredCar(3, 3);
    Unit *rifleman = new Rifleman(3, 5);

    field->addUnit(tank);
    field->addUnit(armoredCar);
    field->addUnit(rifleman);
    field->print();
    //1_________________________________

    field->moveUnit(tank, tank->getx()+1, tank->gety());
    field->moveUnit(armoredCar, armoredCar->getx(), armoredCar->gety()+1);
    field->moveUnit(rifleman, rifleman->getx()-1, rifleman->gety());
    //field->removeUnit(rifleman);
    field->print();
    Damage *damage = new Damage();
    *damage>>tank;
    //std::cout<<"tank "<<();

    //2_________________________________

    Base *base = field->createBase(2,3, 5, 100);
    base->createUnit('C');
    base->createUnit('T');
    base->createUnit('M');
    base->createUnit('S');

    field->print();
    field->printBaseInfo();
     //3_________________________________
}



int main() {

    example1();



    return 0;
}
