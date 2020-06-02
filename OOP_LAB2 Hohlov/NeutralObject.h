//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_NEUTRALOBJECT_H
#define OOP_LAB1_NEUTRALOBJECT_H
#include "GameObject.h"
#include "NeutralObjectStrategy.h"

class Unit;

class NeutralObject: public GameObject {

protected:

    NeutralObjectStrategy *strategy;

public:

    NeutralObject(): GameObject(ObjectType::NEUTRAL_OBJECT){}
    void setStrategy(NeutralObjectStrategy *strategy) { this->strategy = strategy; }
    virtual void applyTo(Unit &unit)=0;

    virtual ~NeutralObject(){

        delete strategy;

    }

};

#endif //OOP_LAB1_NEUTRALOBJECT_H
