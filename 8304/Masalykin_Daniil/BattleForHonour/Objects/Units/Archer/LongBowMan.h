#ifndef BATTLEFORHONOUR_LONGBOWMAN_H
#define BATTLEFORHONOUR_LONGBOWMAN_H


#include "Archer.h"
#include "../../../Armor/Armor.h"

class LongBowMan: public Archer{

public:
    LongBowMan():
        Archer(*ArmorFlyweight::getFlyweight<PlateMail>(), 50){}
};


#endif //BATTLEFORHONOUR_LONGBOWMAN_H
