#ifndef BATTLEFORHONOUR_CROSSBOWMAN_H
#define BATTLEFORHONOUR_CROSSBOWMAN_H


#include "Archer.h"
#include "../../../Armor/Armor.h"

class CrossBowMan: public Archer{

public:
    CrossBowMan():
        Archer(*ArmorFlyweight::getFlyweight<LeatherArmor>(), 100){}
};



#endif //BATTLEFORHONOUR_CROSSBOWMAN_H
