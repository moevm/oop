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
//#include "facade.h"
#include "gamefacade.h"

#include "Rules.h"

void exec2(){
    //Facade<Rule1> facade = Facade<Rule1>::Instance(); //
    GameFacade<Rule2> facade;
    facade.createField();
    facade.play();
}

//-------------------------------
int main() {

    exec2();

    return 0;
}
