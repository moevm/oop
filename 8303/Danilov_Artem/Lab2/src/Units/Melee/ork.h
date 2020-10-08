//
// Created by kot on 08.05.2020.
//

#ifndef ORK_H
#define ORK_H

#include "melee.h"
class Ork : public Melee {
public:
    Ork()
    {
        name = "Orkk";
        characteristics = new Characteristics();
        characteristics->setAll(600, 15, 15);
    };
    std::string getName() {return name;}
    Unit *itemCopy(){
        return new Ork(*this);
    }
};

#endif //ORK_H
