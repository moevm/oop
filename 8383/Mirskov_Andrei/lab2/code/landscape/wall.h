//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_WALL_H
#define OOP_LAB1_WALL_H


#include "landscape.h"

class Wall: public Landscape {
public:
    char getType() override;

    void unitLeft(Unit* unit) override;

    void unitCame(Unit* unit) override;
private:
    const char type = 'w';
};


#endif //OOP_LAB1_WALL_H
