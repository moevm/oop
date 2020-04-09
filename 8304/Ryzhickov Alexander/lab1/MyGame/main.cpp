#include <iostream>
#include "Game/Game.h"
#include <list>
#include "HelpersClasses/NeutralObjects/ArmorGenerator.h"

int main() {

    /* int width;
     int height;
     int maxCountUnits;
     std::cout << " Enter width : ";
     std::cin >> width;
     std::cout << "Enter height : ";
     std::cin >> height;
     std::cout << "Enter max count units : ";
     std::cin >> maxCountUnits;
     auto *field = new Field(width, height, maxCountUnits);*/
    //field->createUnits();

//    field->appendUnits(2,2,2,3);

//    field->show();

    /*Field * field1 = new Field(10,10,0);
    Field * field2 = field1;
    delete(field1);*/

/*    GameCell ** pGameCell = new GameCell *[5];
    for (int i = 0; i < 5; ++i) {
        pGameCell[i] = new GameCell[4];
    }

    GameCell * oper = pGameCell[2];*/
  Game *game = new Game();
  delete(game);

   /* UnitFactory *unitFactory = new UnitFactory();

    Swordmen *swordsmen = unitFactory->getSwordsmen();

    std::cout << swordsmen->getArmor();
    int *a = swordsmen->getArmorForGenerator();

//    int b = 5;
    auto*armorGenerator = new ArmorGenerator;
    (*armorGenerator)[a];
//    std::cout << b;
    std::cout << swordsmen->getArmor();*/

    return 0;
}