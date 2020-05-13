//
// Created by kot on 08.05.2020.
//

#ifndef WITCH_H
#define WITCH_H

#include "support.h"

class Witch : public Support {
    // support 2 death and  all_char/3 orks
public:
    Witch()
    {
        name = "Witch";
	    characteristics = new Characteristics();
        characteristics->setAll(1500, 35, 60);
    };
    std::string getName() {return name;}
    Unit *itemCopy(){
        return new Witch(*this);
    }
};
#endif //WITCH_H
