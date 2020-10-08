//
// Created by kot on 08.05.2020.
//

#ifndef DRAGON_H
#define DRAGON_H
#include "range.h"

class Dragon : public Range{
public:
    Dragon()
    {
        name = "Dragon";
	    characteristics = new Characteristics();
        characteristics->setAll(1200, 100, 90);
    };
    std::string getName() {return name;}
    Unit *itemCopy(){
        return new Dragon(*this);
    }
};

#endif //DRAGON_H
