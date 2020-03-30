#ifndef LAB2_LANDSCAPE_H
#define LAB2_LANDSCAPE_H

#include "HealthPoints.h"
#include "Attack.h"

class Landscape {
public:
    Landscape() = default;
    Landscape(int def, int att, int intell, bool stand) : defense(def), attack(att), intelligence(intell), can_stand(stand) {}
    HealthPoints defense;
    Attack attack;
    int intelligence{};
    bool can_stand{};
};


#endif
