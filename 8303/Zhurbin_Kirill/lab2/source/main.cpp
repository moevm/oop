#include <iostream>
#include "Field.h"
#include "Iterator.h"
#include "Base.h"
#include "Poisen.h"
#include "Potion.h"
#include "DrinkStrong.h"
#include "DrinkStamina.h"

int main() {

    Field* field = new Field(8, 8, 6);
    field->addLandscape();
    field->printLandscape();


    std::cout << "---------------------------"<< std::endl;

    field->addNeutral(1, 1, 'z');
    field->addNeutral(2, 2, 'p');
    field->addNeutral(3, 3, 's');
    field->addNeutral(4, 4, 'a');
    field->printNeutral();
    std::cout << "---------------------------"<< std::endl;


    Base* base = field->createBase(3, 4, 8, 100);
    base->createUnit('o');
    base->createUnit('y');
    base->createUnit('k');
    base->createUnit('s');
    base->createUnit('y');
    base->createUnit('h');
    base->createUnit('y');
    base->createUnit('h');
    field->printAll();


    std::cout << "---------------------------"<< std::endl;
    Iterator iter(*field);
    while (iter.hasNext()){
            std::cout << (*iter)->condition.armor << std::endl;
    }

    DrinkStaminaAction* drinkStamina = new DrinkStaminaAction(new DrinkStaminaTankman);

    Iterator iter1(*field);
    while (iter1.hasNext()){
        *drinkStamina >> *iter1;
    }

    std::cout << "---------------------------"<< std::endl;
    Iterator iter2(*field);
    while (iter2.hasNext()){
        std::cout << (*iter2)->condition.armor << std::endl;
    }

    std::cout << "---------------------------"<< std::endl;


    std::cout << "---------------------------"<< std::endl;

    Iterator iter3(*field);
    while (iter3.hasNext()){
        std::cout << (*iter3)->condition.health << std::endl;
    }

    PotionAction* potion = new PotionAction(new PotionTankman);

    Iterator iter4(*field);
    while (iter4.hasNext()){
        *potion >> *iter4;
    }

    std::cout << "---------------------------"<< std::endl;
    Iterator iter5(*field);
    while (iter5.hasNext()){
        std::cout << (*iter5)->condition.health << std::endl;
    }

    std::cout << "---------------------------"<< std::endl;

    return 0;
}
