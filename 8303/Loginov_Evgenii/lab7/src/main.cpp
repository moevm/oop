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

#include "Exceptions.h"

#include "Rules.h"

void execGameRule(){
    //Facade<Rule1> facade = Facade<Rule1>::Instance(); //сиглтон
    GameFacade<Rule2> facade;
    facade.createField();
    facade.play();
}

void execFacade(){
//    Facade *facade = new Facade();
//    facade->createField();
//    facade->play();
}

//-------------------------------
int main() {

    try {
        execGameRule();
    }
    catch(InputException e) {
        std::cout << e.typeOfError() << std::endl;
    }
    catch(LogicException e) {
        std::cout << e.typeOfError() << std::endl;
    }

    return 0;
}
