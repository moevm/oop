#ifndef LAB2_NEUTRALOBJECT_H
#define LAB2_NEUTRALOBJECT_H


#include <HealthPoints.h>
#include <Attack.h>

class NeutralObject {
public:
    NeutralObject(int def, int att, int intell) : defense(def), attack(att), intelligence(intell) {}
    HealthPoints defense;
    Attack attack;
    int intelligence{};
};


#endif
