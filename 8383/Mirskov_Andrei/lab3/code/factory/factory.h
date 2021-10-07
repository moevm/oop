//
// Created by andrei on 26.02.2020.
//

#ifndef OOP_LAB1_FACTORY_H
#define OOP_LAB1_FACTORY_H

#include "../units/elephantman.h"
#include "../units/spearman.h"
#include "../units/swordman.h"
#include "../units/horseman.h"
#include "../units/wooden.h"
#include "../units/firearcher.h"
#include "../neutral/neutral.h"
#include "../neutral/clothes.h"
#include "../neutral/kit.h"
#include "../neutral/weapon.h"
#include "../neutral/potion.h"

class Factory {
public:
    static Unit* createUnit(Base* base,char type);

    static Neutral* createNeutral(char type);
};


#endif //OOP_LAB1_FACTORY_H
