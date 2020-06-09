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
#include "GameFacade.h"
#include "Exceptions.h"
#include "Rules.h"

#include "Neutral/NeutralObject.h"

void execGameRule(){ // Игра по одному из двух правил

    //обратотка исключений
    try {
        GameFacade<Rule2>& facade = GameFacade<Rule2>::Instance(); //сиглтон
        //GameFacade<Rule1> facade1 = GameFacade<Rule1>::Instance();
        //GameFacade<Rule2> facade;
        facade.createField();

        std::cout << "Iterate throw field!" << std::endl;
        Field* field = facade.getField();
        Iterator iter1(field);
        while (iter1.goNext()){
            Cell* cell = *iter1;
            std::cout << cell->y << " " << cell->x << " ";

            if(cell->object!= nullptr) {
                std::cout << "(" << cell->object->typeNeutral() << ", ";
            }
            else {
                std::cout << " ";
            }

            if(cell->landscape!= nullptr) {
                std::cout << cell->landscape->typeLandscape() << ")" << std::endl;
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;

        facade.play();
    }
    catch(InputException e) {
        std::cout << e.typeOfError() << std::endl;
    }
    catch(LogicException e) {
        std::cout << e.typeOfError() << std::endl;
    }

}

void execFacade(){ // Режим без правил, 1 игрок
//    Facade *facade = new Facade();
//    facade->createField();
//    facade->play();
}


int main() {

    execGameRule();

    return 0;
}
