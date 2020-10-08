//
// Created by kot on 08.05.2020.
//

#ifndef CHIMERA_H
#define CHIMERA_H

#include "range.h"

class Chimera : public Range {
public:
    Chimera(){
        name = "Chimera";
	    characteristics = new Characteristics();
        characteristics->setAll(1000, 80, 50);
    };
    std::string getName() {return name;}
    Unit *itemCopy(){
        return new Chimera(*this);
    }
};

#endif //CHIMERA_H
