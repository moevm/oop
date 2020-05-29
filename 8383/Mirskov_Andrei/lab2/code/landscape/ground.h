//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_GROUND_H
#define OOP_LAB1_GROUND_H


#include "landscape.h"

class Ground: public Landscape {
public:
    char getType() override;

    void unitLeft(Unit* unit) override;

    void unitCame(Unit* unit) override;

private:
    const char type = 'g';
};


#endif //OOP_LAB1_GROUND_H
