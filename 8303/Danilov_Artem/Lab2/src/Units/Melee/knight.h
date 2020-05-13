//
// Created by kot on 08.05.2020.
//

#ifndef KNiGHT_H
#define KNiGHT_H
#include "melee.h"

class Knight : public Melee{
public:
    Knight(){
        name = "Knight";
	    characteristics = new Characteristics();
        characteristics->setAll(500, 20, 30);
    };
    std::string getName() {return name;}
    Unit *itemCopy(){
        return new Knight(*this);
    }
};


#endif //KNiGHT_H
