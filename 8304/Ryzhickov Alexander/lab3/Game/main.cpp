#include <iostream>
#include "Game/Game.h"
#include "OtherClasses/NeutralObjects/Generators/ArmorGenerator.h"
#include "OtherClasses/Landscapes/ProxyLandscape.h"

int main() {

    Game *game = new Game();


    // Демонстрационный пример работы генератора черех перегрузку оператора []
    /* auto *unitFactory = new UnitFactory();
     Swordmen *swordsmen = unitFactory->getSwordsmen();
     std::cout << swordsmen->getArmor() << "\n";
     auto *armorGenerator = new ArmorGenerator;
     (*armorGenerator)[swordsmen->getArmorForGenerator()];
     std::cout << swordsmen->getArmor();*/

    /* auto *unitFactory = new UnitFactory();
     Unit *swordsmen = unitFactory->getArcher();
     Landscape *forest = new ForestLandscape();
     auto *proxyLandscape = new ProxyLandscape(forest);

     proxyLandscape->getBonus(swordsmen);

     std::cout << swordsmen->getAttackBonus()<<std::endl;*/

    int array [4];
    game->getInformationAboutEnvironment(array,9,4);

    for (int i = 0; i < 4; ++i) {
        std::cout << array[i] << " ";
    }

    std::cout << "\n";


    delete (game);

    /*if (typeid(*swordsmen) == typeid(RangedUnit)) {
        return 25;
    } else {
        return 0;
    }*/

    //std::cout << std::is_same<decltype(swordsmen), class Archer>::value <<std::endl;;

    //if(dynamic_cast<AttackUnitArmor *>(swordsmen) != nullptr) std::cout << "br";
    return 0;
}